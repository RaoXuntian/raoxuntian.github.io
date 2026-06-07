#include <iostream>
using namespace std;

class person
{
protected:
	double money;
public:
	int height;
	int weight;
	string name;
	person(const person &p){cout << "person(person p)\n";};
	person():height(180), weight(100), name("Jack"){cout << "person()\n";};
	person(const string s):height(180), weight(100), name(s) {cout << "person(string name)\n";};
	person(int a, int b, const string s):height(a), weight(b), name(s){cout << "person(int height, int weight, string name)\n";};
	virtual ~person(){cout << "~person()\n";};
	virtual void getMoney(double x) {money+=x;};
	virtual void costMoney(double x) {money-=x;};
	virtual void slogan(){cout << "I am a person." << endl;};
	virtual void slogan(string s){cout << "I am a " << s << "." << endl;};
	void judge() {if (money>0) cout << name << "是有钱人！\n"; else cout << name << "是穷逼！\n";};
	double remainMoney() {return money;};

};

class testSex: public person
{
private:
	bool sex;
public:
	void show(){cout << height << " " << weight << " " << name << endl;};
};

class boy: public person
{
private:
	bool sex;
public:
	boy():sex(true){cout << "boy()\n";};
	boy(const string s):sex(true), person(s) {cout << "boy(string name)\n";};
	boy(int a, int b, const string s):sex(true), person(a, b, s) {cout << "boy(int height, int weight, string name)\n";};
	~boy(){cout << "~boy()\n";};
	void getSex(){string sexx; sexx=sex?"Boy":"Girl"; cout << name << " is a " << sexx << endl;};
	void getMoney(double x) {money+=x*2;};
	void costMoney(double x) {money-=x*0.5;};
	void slogan(){cout << "I am a boy." << endl;};
};

class girl: public person
{
private:
	bool sex;
public:
	girl():sex(false){cout << "girl()\n";};
	girl(const string s):sex(false), person(s) {cout << "girl(string name)\n";};
	girl(int a, int b, string s):sex(false), person(a, b, s){cout << "girl(int height, int weight, string name)\n";};
	~girl(){cout << "~girl()\n";};
	void getSex(){string sexx; sexx=sex?"Boy":"Girl"; cout << name << " is a " << sexx << endl;};
	void getMoney(double x) {money+=x*1.5;};
	void costMoney(double x) {money-=x*3;};
	void slogan(){cout << "I am a girl." << endl;};
};

int main(int argc, char const *argv[])
{
/*
	person a;
	cout << a.height << " " << a.weight << " " << a.name << endl;
	a.costMoney(50);
	a.judge();
	person *b = new person(178, 160, "Tom");
	b->getMoney(100);
	b->judge();
	//a.money();	//error: 'money' is a private member of 'person'
	cout << a.name << "还有" << a.remainMoney() << "元。" << endl;
	cout << b->name << "还有" << b->remainMoney() << "元。" << endl;

	boy c(100, 200, "Milky");
	girl d("Rose");
	boy e;
	c.getSex();
	d.getSex();
	testSex test;
	test.show();
	//girl *f = new person();	// error!
	person *f = new girl();
	cout << f->remainMoney() << endl;
	delete f;
*/
	person g;
	boy h;
	girl i;
	g.slogan();
	g.slogan("doctor");
	h.slogan();
	i.slogan();
	person j = i;
	person &j_ref = i;
	person *j_p = &i;
	j.slogan();
	j_ref.slogan();
	j_p->slogan();
	j_ref.getMoney(10);
	j_ref.costMoney(10);
	j_ref.judge();
	cout << j_ref.remainMoney() << endl;
	return 0;
}