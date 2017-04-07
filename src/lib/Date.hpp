#pragma once

#ifndef SJTU_DATE_HPP
#define SJTU_DATE_HPP

namespace sjtu {
	class Date {
		class date {
			//只表示年份，不用来表示差值
			class year {
				int val;
			public:
				year() {}
				year(int val) :val(val) {}
				year(const year& ex) {
					val = ex.val;
				}
				bool isLeap() {
					return (val % 400 == 0) || (val % 4 == 0 && val % 100);
				}
				//两个年份
				int operator-(year ex) {
					return val - ex.val;
				}
				/*	year operator++(int x) {
				year temp = *this;
				val += 1;
				return temp;
				}*/
				year& operator++() {
					val += 1;
					return *this;
				}
				operator int() {
					return val;
				}
			};

			//val为1-based
			class month {
				int val;
			public:
				month() {}
				month(int val) :val(val) {}
				month(const month& ex) {
					val = ex.val;
				}
				int operator-(month ex) {
					return val - ex.val;
				}
				operator int() {
					return val;
				}
			};

			//val为1-based
			class day {
				int val;
			public:
				day() {}
				day(int val) :val(val) {}
				day(const day& ex) {
					val = ex.val;
				}
				int operator-(day ex) {
					return val - ex.val;
				}
				void operator+=(int add) {
					val += add;
				}
				void operator-=(int sub) {
					val -= sub;
				}
				operator int() {
					return val;
				}
			};

			//hour 和 minute 为1-based
			class time {
				int hour;
				int minute;
			public:
				time() {}
				time(int hour, int minute) :hour(hour), minute(minute) {}
				time(const time& ex) {
					hour = ex.hour;
					minute = ex.minute;
				}
				int operator-(time ex) {
					return (hour - ex.hour) * 60 + (minute - ex.minute);
				}
				int operator+(int add) {
					int cnt = 0;
					hour += add / 60;
					minute += add % 60;
					if (minute >= 60) ++hour, minute -= 60;
					if (hour >= 24) ++cnt, hour -= 24;
					return cnt;
				}
			};

			static const int daySum2[13];
			static const int dayNum[13];
			static const int daySum[13];

			year y;
			month m;
			day d;
			time t;

			//repair需要保证a < b
			int repair(date a, date b) {
				int cnt = 0;
				if (a.y.isLeap() && a.m <= 2) ++cnt;
				if (b.y.isLeap() && a.m >= 3) ++cnt;
				int fisrtYear = a.y + 1;
				int lastYear = b.y;
				for (int i = fisrtYear; i < lastYear; ++i) {
					if (year(i).isLeap()) ++cnt;
				}
				return cnt;
			}
			int between(date a, date b) {
				int firstYear = a.y + 1;
				int lastYear = b.y;
				int cnt = 0;
				cnt += dayNum[a.m] - a.d;
				cnt += daySum[12] - daySum[a.m];
				cnt += b.d;
				cnt += daySum[int(b.m) - 1];
				cnt += (lastYear - firstYear) * 365;
				cnt += repair(a, b);
				return cnt;
			}
		public:
			date() {}
			date(year y, month m, day d, time t) :y(y), m(m), d(d), t(t) {}
			date(const date& ex) :y(ex.y), m(ex.m), d(ex.d), t(ex.t) {}
			int operator-(const date& ex) {
				return between(ex, *this) * 1440 + (t - ex.t);
			}
			friend date operator+(date a, int add) {
				date temp = a;
				temp.d += (add / 1440) + (temp.t + (add % 1440)); // t operator+ 改变自己同时返回值
				temp.d += daySum[int(temp.m) - 1];
				temp.m = 1;
				while (temp.d > 366) {
					if (temp.y.isLeap()) ++temp.y, temp.d -= 366;
					else ++temp.y, temp.d -= 365;
				}
				if (temp.d == 366 && !temp.y.isLeap()) ++temp.y, temp.d -= 365;
				if (temp.y.isLeap()) {
					for (int i = 12; i > 0; --i) {
						if (temp.d > daySum2[i - 1]) {
							temp.d -= daySum2[i - 1];
							temp.m = i;
							break;
						}
					}
				}
				else {
					for (int i = 12; i > 0; --i) {
						if (temp.d > daySum[i - 1]) {
							temp.d -= daySum[i - 1];
							temp.m = i;
							break;
						}
					}
				}
				return temp;
			}
			bool operator>(date ex) {
				if (y > ex.y) return true;
				else if (m > ex.m) return true;
				else if (d > ex.d) return true;
				else if (t - ex.t >= 0) return true;
				else return false;
			}
		};

		date dt;
	public:
		Date() {}
		Date(const date& dt) :dt(dt) {}
		Date(const Date& ex) :dt(ex.dt) {}
		//对Date a b 的先后没有区分， 可以返回负值
		friend int operator-(Date a, Date b) {
			if (a.dt > b.dt) return a.dt - b.dt;
			else return -(b.dt - a.dt); // date::operator- 必须保证前面大于后面
		}
		//int b 需要保证非负（后续看情况添加可以为负的情况）
		friend Date operator+(Date a, int b) {
			return Date(a.dt + b);
		}
	};
}

const int sjtu::Date::date::daySum[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int sjtu::Date::date::daySum2[13] = { 0,31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
const int sjtu::Date::date::dayNum[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

#endif