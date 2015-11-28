

Database::Database(): gameList(){

}

Database& Database::getInstance(){
  static Database instance;
  return instance;
}

