#include "..\headers\maploader.h"

TileType chooseTileType( char c );
TileType chooseTileType( std::string str );

MapLoader::MapLoader(){
	objects = new std::vector<MapObject*>();
	strToTileTypeMap = new std::map<std::string, TileType>();

	(*strToTileTypeMap)["wall"] = TILE_CENTER;
}

MapLoader::~MapLoader(){
	delete strToTileTypeMap;
	for(auto it = objects->begin(); it != objects->end(); it++){
		delete *it;
	}
	delete objects;
}

void MapLoader::clear(){
	objects->clear();
	mapWidth = 0;
	mapHeight = 0;

}

Map* MapLoader::createMap(){
	Map* map = NULL;
	int mapWidth=25;
	int mapHeight=25;
	int mapSize = mapWidth*mapHeight;
	
	Tile** tiles = new Tile*[mapSize];
	for(int i=0; i<mapSize; i++){
		tiles[i] = new Tile();
	}

	for(int i=0; i<mapWidth; i++){
		for(int j=0; j<mapHeight; j++){
			TileType t = TileType::TILE_GREEN;
			if( i==0 || j==0 ||
				i==mapWidth-1 || j==mapHeight-1){
					t = TileType::TILE_CENTER;
			}
			int pos = i*mapHeight+j;
			tiles[pos]->setType(t);
		}
	}
	
	map = new Map(tiles, mapWidth, mapHeight, new Vector2D(1,1), new Vector2D(mapWidth-2,mapHeight-2));

	return map;
}

Map* MapLoader::loadMap(std::string fileName){
	using namespace std;
	Map* map = NULL;

	ifstream file (fileName, ios::in);

	if( file.is_open()){
		std::cout << "Start load..." << std::endl;
		std::cout << "Parsing..." << std::endl;

		while ( file.good() ){
			std::string line;
			getline (file,line);
			parseLine(line);
		}

		file.close();
		std::cout << "Load Complete!" << std::endl;
	}
	else{
		std::cout << "Error openining " + fileName << std::endl;
	}

	//Create the basic Map internal data
	int mapSize = mapWidth*mapHeight;
	Tile** tiles = new Tile*[mapSize];
	for(int i=0; i<mapSize; i++){
		tiles[i] = new Tile();
	}

	for(int i=0; i<objects->size(); i++){
		MapObject* obj = objects->at(i);
		switch(obj->objType){
			case MapObject::objectType::tile :
				Tile* tile = tiles[obj->y*mapWidth+obj->x];
				tile->setType(obj->tileType);
				break;
		}
		
		delete obj;
	}

	map = new Map(tiles, mapWidth, mapHeight, new Vector2D(0,0), new Vector2D(20,20));

	this->clear();
	return map;
}


void MapLoader::parseLine(std::string line){
	const std::string meta_token = "META";
	const std::string object_token = "OBJECT";
	const std::string header_token = "HEADER";

	//Identify the type of line being parsed
	//	remove the identifier and trailing space before passing to 
	//	specific parser
	if(line.empty()){
		return;
	}else if(line.find(header_token)!=std::string::npos){ 
		parseHeader(line.substr(header_token.size()+1));
	}else if(line.find(meta_token)!=std::string::npos){
		parseMeta(line.substr(meta_token.size()+1));
	}else if(line.find(object_token)!=std::string::npos){
		parseObject(line.substr(object_token.size()+1));
	}else{
		return;
	}
}

//For lines that contain headers within the map file
void MapLoader::parseHeader(std::string line){
}

//Read metadata about the map stored in this meta line
void MapLoader::parseMeta(std::string line){
	const std::string width_token = "width";
	const std::string height_token = "height";
	
	std::stringstream stream(line);
	std::string tmp;
	while( getline(stream, tmp, ' ') ){
		if(tmp==width_token){
			getline(stream, tmp, ' ');
			this->mapWidth = atoi(tmp.c_str());
		}else if(tmp==height_token){
			getline(stream, tmp, ' ');
			this->mapHeight = atoi(tmp.c_str());
		}
	}

}

//Create and fill in a new object using the values read in line
void MapLoader::parseObject(std::string line){
	const std::string tile_token = "tile";
	const std::string id_token = "id";
	const std::string x_token = "x";
	const std::string y_token = "y";
	const std::string tiletype_token = "type";
	const std::string iscollidable_token = "isCollidable";

	MapObject* newObject = new MapObject();

	std::stringstream stream(line);
	std::string tmp;
	while( getline(stream, tmp, ' ') ){
		if(tmp==tile_token){
			getline(stream, tmp, ' ');
			newObject->objType = MapObject::objectType::tile;
		}else if(tmp==id_token){
			getline(stream, tmp, ' ');
			newObject->id = atoi(tmp.c_str());
		}else if(tmp==x_token){
			getline(stream, tmp, ' ');
			newObject->x = atoi(tmp.c_str());
		}else if(tmp==y_token){
			getline(stream, tmp, ' ');
			newObject->y = atoi(tmp.c_str());
		}else if(tmp==tiletype_token){
			getline(stream, tmp, ' ');
			newObject->tileType = (*strToTileTypeMap)[tmp];
		}else if(tmp==iscollidable_token){
			getline(stream, tmp, ' ');
			newObject->isCollidable = atoi(tmp.c_str());
		}
	}
	this->objects->push_back(newObject);
}




