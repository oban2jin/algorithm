#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MAX_CAR = 1000000;

struct Car{
	int age;
	int partition;
	int engine;
	int price;
};

void buy(Car *car)
{
	car->age = rand()%20;
	car->partition = 2 + rand()%11;
	car->engine = 1000 + rand()%4000;
	car->price = 10000 + rand()%30000;
}

extern void store(Car car);

extern void filter_age(int from, int to);
extern void filter_partition(int from, int to);
extern void filter_engine(int from, int to);
extern void filter_price(int from, int to);

extern int sell();

extern void refund(int order_number);

extern int stock(void);

int MW=-1,MC=-1;
int main()
{
	int TS = 10;
	int order_number, refund_number = -1;

	srand(3);

	clock_t T1 = clock();

	for(int t = 1; t <= TS; t++)
	{
		for(int i = 1; i <= MAX_CAR; i++)
		{
			Car *car = new Car();

			buy(car);
			store(*car);

			if(i%100==0)
			{
				filter_age(rand()%20,rand()%20);
				filter_partition(2+rand()%11,2+rand()%11);
				filter_engine(1000+rand()%4000,1000+rand()%4000);
				filter_price(10000+rand()%30000,10000+rand()%30000);

				order_number = sell();
				if(rand()%10 == 0) 
					refund_number = order_number;
			}
			if(i%10000==0)
			{
				if(refund_number != -1)
				{
					refund(refund_number);
					refund_number=-1;
				}
			}
		}

		int STOCK = stock();
		refund_number = -1;
		printf("STOCK : %d\n",STOCK);
	}

	clock_t T2 = clock();
	long PERFORMENCE = T2-T1;
	
	printf("PERFORMENCE : %ld\n",PERFORMENCE);
	printf("MW=[%d],MC=[%d]\n",MW,MC);
	return 0;
}
/*user.cpp*/

const int MAXL=500,MAXCAN=15000,MAXSELL=100;
const int VALUEKEY=100000;
int filter_from=0, filter_to=0;
int _fE,_tE,_fPR,_tPR;
int _OrderNo=0,_StockCnt=0,_TCanCnt=0;
int W[1<<13][MAXL];
struct S{
	int f,t;
}SELL[MAXSELL];
struct Trash{
	int idx,value;
}CAN[MAXCAN];
int getIndexNo(int a,int pt,int e,int pr){
	int index=0;
	index += (a << 8); index += (pt-2)<<4; index += (e-1000)/1000<<2; index += (pr-10000)/10000;
	return index;
}
void swap(int& a,int &b){
	a=a^b; b=a^b; a=a^b;
}
void store(Car car) {
	int idx = getIndexNo(car.age,car.partition,car.engine,car.price);
	int value = car.engine*VALUEKEY+car.price;
	int& cnt = W[idx][0]; W[idx][++cnt]=value; ++_StockCnt;
	if(MW<cnt)MW=cnt;
}

void filter_age(int from, int to) {
	if(to<from)swap(from,to);
	filter_from += (from << 8); filter_to += (to<<8);
}

void filter_partition(int from, int to) {
	if(to<from)swap(from,to);
	filter_from += (from-2)<<4; filter_to += (to-2)<<4;
}

void filter_engine(int from, int to) {
	if(to<from)swap(from,to); _fE = from , _tE=to;
	filter_from += ((from-1000)/1000)<<2; filter_to += ((to-1000)/1000)<<2;
}

void filter_price(int from, int to) {
	if(to<from)swap(from,to); _fPR = from, _tPR=to;
	filter_from+=(from-10000)/10000; filter_to+= (to-10000)/10000;
}

int sell() {
	++_OrderNo; int bTCanCnt = _TCanCnt; bool sellFlag=false;
	for(int i=filter_from;i<=filter_to;i++){
		int& cnt = W[i][0];for(int j=1;j<=cnt;j++){
			int value=W[i][j];int engine=value/VALUEKEY; int price=value%VALUEKEY;
			if(_fE<=engine && engine <= _tE && _fPR<=price && price <= _tPR){
				// printf("value=[%d], _E=[%d][%d], _PR=[%d][%d]\n",value,_fE,_tE,_fPR,_tPR);
				sellFlag = true;
				// //Refund를 위한 자료 저장으로 이동
				--_StockCnt,CAN[++_TCanCnt]={i,value}; 
				if(MC<_TCanCnt)MC=_TCanCnt;
				W[i][j]=W[i][cnt--]; j--; 
			}
		}
	}
	if(sellFlag)SELL[_OrderNo] = {bTCanCnt+1,_TCanCnt};
	else SELL[_OrderNo]={0,0};
	//clear filter index
	filter_from = 0, filter_to=0;
	//printf("_OrderNo=[%d],sellFlag=[%d]\n",_OrderNo,sellFlag);
	return _OrderNo;
}

void refund(int order_number) {
	// printf("Refund =>[%d] ~ ",_StockCnt);
	S rf = SELL[order_number]; if(rf.f!=0 && rf.t!=0){
		for(int i=rf.f; i<=rf.t;i++){
			int idx = CAN[i].idx; int value = CAN[i].value; 
			int& cnt = W[idx][0]; W[idx][++cnt]=value; 
			++_StockCnt;
		}
	}
	// printf("Refund =>[%d]\n",_StockCnt);
	_OrderNo = 0; _TCanCnt = 0;
}

int stock(void) {
	return _StockCnt;
}
