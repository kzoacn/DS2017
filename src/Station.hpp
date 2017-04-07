class Station{
private:
	string id;
public:
	Station(){}
	Station(const string &_id):id(_id){}
	const string& getName(){
		return id;
	}
};
