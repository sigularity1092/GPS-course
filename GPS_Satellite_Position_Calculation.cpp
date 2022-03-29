#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	//参数列表
	const long double GM = 3.986005e14;             //地球重力场参数 m^3/s^2
	const long double Omegae_dot = 7.2921151467e-5; //地球自传速率, rad/s
	long double roota = 5.153666322710E+03;//长半轴开根号
	long double t = 43202;                      //观测时刻
	long double toe = 4.320000000000E+05;//星历参考时间
	long double i0 = 9.635717531800E-01;//轨道倾角
	long double idot = 2.571535692720E-11;//轨道倾角改正项
	long double M0 = -2.035276974570E+00;//参考时刻平近点角
	long double omega = 9.439658333370E-01;//近地点角距
	long double deltan = 5.256647561680E-09;//平均角速度改正项
	long double ecc = 3.840906778350E-03;//偏心率
	long double crs = -1.497187500000E+02;
	long double cuc = -7.661059498790E-06;
	long double cus = 1.081451773640E-05;
	long double cic = 3.539025783540E-08;
	long double cis = -8.381903171540E-08;
	long double crc = 1.741562500000E+02;
	long double Omega0 = -1.000540496180E-01; //参考时刻升交点的赤经
	long double Omegadot = -7.652461775360E-09;//升交点赤经变化率

	//1、计算卫星运行的平均角速度n
	long double a = roota * roota;//轨道长半轴
	long double n0 = sqrt(GM / a*a*a);
	long double n = n0 + deltan;

	//2、计算t时刻卫星的平近点角 M
	long double M = M0 + n * (t - toe);

	//3、迭代2次计算t时刻卫星的偏近点角 E
	long double E = M;
	for (int i = 0; i < 2; i++)
		E= M + ecc * sin(E);

	//4、计算卫星的地心矢距 r1
	long double r1 = a * (1.0 - ecc * cos(E));

	//5、计算真近点角 f
	long double f = atan2(sqrt(1.0 - ecc * ecc) * sin(E), cos(E) - ecc);
	//long double f = atan(sqrt(1.0 - ecc * ecc) * sin(E)/(cos(E) - ecc));

	//6、计算升交距角（未经改正的）
	long double u1 = omega + f;

	//7、计算摄动改正项：delte_u，delta_r，delta_i
	long double delta_u = cus * sin(2.0 * u1) + cuc * cos(2.0 * u1);
	long double delta_r = crs * sin(2.0 * u1) + crc * cos(2.0 * u1);
	long double delta_i = cis * sin(2.0 * u1) + cic * cos(2.0 * u1);

	//8、对 u1,r1,i0 进行摄动改正
	long double u = u1 + delta_u;
	long double r = r1 + delta_r;
	long double i = i0 + idot * (t - toe) + delta_i;

	//9、计算卫星在轨道面坐标系中的位置
	long double x = r * cos(u);
	long double y = r * sin(u);

	//10、计算观测时刻升交点的经度L
	long double L = Omega0 + Omegadot *(t-toe) - Omegae_dot * t;

	//11、计算卫星在地固坐标系下的坐标
	long double X = x * cos(L) - y * cos(i) * sin(L);
	long double Y = x * sin(L) + y * cos(i) * cos(L);
	long double Z = y * sin(i);

	//输出地固坐标系下的坐标
	cout <<"地固坐标系下的坐标:" << endl;
	cout <<"X:" << X << endl;
	cout <<"Y:" << Y << endl;
	cout <<"Z:" << Z << endl;

	return 0;
}
