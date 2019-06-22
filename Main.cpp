#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "NhanVien.h"
#include <iomanip>
#include <cstdlib>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <locale>
#include <codecvt> //possible C++11?
using namespace std;

int StringToInt(wstring NumberAsString) {
	int NumberAsInt;
	wstringstream ss;
	ss << NumberAsString;
	ss >> NumberAsInt;
	return NumberAsInt;
}
wstring IntToString(int NumberAsInt) {
	wstring NumberAsString;
	wstringstream ss;
	ss << NumberAsInt;
	ss >> NumberAsString;
	return NumberAsString;
}
float StringToFloat(wstring NumberAsString) {
	float NumberAsFloat;
	wstringstream ss;
	ss << NumberAsString;
	ss >> NumberAsFloat;
	return NumberAsFloat;
}
string	FloatToString(float NumberAsFloat) {
	string NumberAsString;
	stringstream ss;
	ss << NumberAsFloat;
	ss >> NumberAsString;
	return NumberAsString;
}

bool equal(wchar_t x, wchar_t y) {
	return (x == y) ? true : false;
}
bool equal(wstring x, wstring y) {
	//int pos = 0;
	//if (x[0] == y[0]) {
	//	while (x[pos] != '\0' && y[pos] != '\0') {
	//		if (x[pos] != y[pos]) return false;
	//		else pos++;
	//	}
	//	return true;
	//}
	//else return false;
	return (x == y) ? true : false;
}
bool equal(wstring x, wchar_t y) {
	int pos = 0;
	while (x != L"\0")
	{
		if (x[pos] == y)
			return true;
		else pos++;
	}
	return false;
}
int getIntRange(int low, int high)
{
	int n;
	while (true)
	{
		wcin >> n;
		if (n < low || n > high)
			wcout << L"GIÁ TRỊ LỖI!\n";
		else
			break;
	}
	return n;
}
wstring toLower(const wstring input) {
	wstring str = input;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') {
			//Convert lowercase to uppercase 
			//str[i] = str[i] - 32;
			continue;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			//Convert uppercase to lowercase 
			str[i] = str[i] + 32;
		}
	}
	return str;
}
wstring toUpper(const wstring input) {
	wstring str = input;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') {
			//Convert lowercase to uppercase 
			str[i] = str[i] - 32;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			//Convert uppercase to lowercase 
			//str[i] = str[i] + 32;
			continue;
		}
	}
	return str;
}

wstring background(wstring n, int size) {
	int temp = size - (n).length();
	if (temp < 0) {
		return n;
	}
	else {
		for (int i = 0; i < temp; i++)
		{
			n += ' ';
		}
	}
	return n;
}
wstring background(wchar_t x, int size) {
	wstring temp = &x;
	for (int i = 0; i < size; i++)
	{
		temp += x;
	}
	return temp;
}

int Find(wstring info, wchar_t x)
{
	int pos = 0;
	while (info[pos] != '\0')
	{
		if (equal(info[pos], x)) {
			return pos;
		}
		else if (info[pos + 1] == '\0') {
			return pos + 1;
		}
		else pos++;
	}
	/*for (int i = 0; i < info.length(); i++)
	{
	if (equal(info[i], x)) {
	return i;
	}
	}
	*/
}

wstring* Split(wstring info, wchar_t x) {
	wstring* substring = new wstring[118];
	int found, pos = 0;
	wstring temp = info;
	while (temp != L"\0") {
		found = Find(temp, x);
		for (int i = 0; i < found; i++)
		{
			substring[pos] += temp[i];
		}
		temp.erase(0, found + 1);
		pos++;
	}
	return substring;
}
Date outputBOD(wstring info) {
	wstring* a = Split(info, '/');
	Date ns;
	if (a->length() < 0) {
		ns.ngay = -1;
		ns.thang = -1;
		ns.nam = -1;
	}
	else {
		ns.ngay = StringToInt(*a);
		ns.thang = StringToInt(*(a + 1));
		ns.nam = StringToInt(*(a + 2));
	}
	return ns;
}
wstring BODtoSTR(Date ns) {
	wstring x;
	wstring d, m, y;

	if (ns.ngay < 10 && ns.ngay > 0) {
		d = L'0' + IntToString(ns.ngay);
	}
	else d = IntToString(ns.ngay);
	if (ns.thang < 10 && ns.thang>0) {
		m = L'0' + IntToString(ns.thang);
	}
	else m = IntToString(ns.thang);
	if (ns.nam > 0 && ns.nam < 1180) {
		y = L'0' + IntToString(ns.nam);
	}
	else y = IntToString(ns.nam);

	x = d + L'/' + m + L'/' + y;

	return x;
}
struct LinkedList {
	NhanVien data;
	struct LinkedList* next;
};
typedef LinkedList* list;//Thay kiểu dữ liệu = list cho ngắn gọn

list creatList(NhanVien value) {
	list temp; //Khai báo 1 list
			   //temp = (list)malloc(sizeof(struct LinkedList));//Cấp phát vùng nhớ dùng malloc
	temp = new LinkedList;
	temp->next = NULL; //cho next trỏ tới NULL
	temp->data = value; //gán giá trị cho list
	return temp;//trả về list mới đã có giá trị
}
list addl(list l, NhanVien value) {
	list temp = creatList(value);//khởi tạo list temp với data = value
	if (l == NULL) {
		l = temp; //nếu liked list đang trống thì list temp là l
	}
	else {
		temp->next = l; //trỏ next của temp = l hiện tại
		l = temp; //đổi l hiện tại = temp (vì temp bây h là l mới)
	}
	return l;
}
list addTail(list l, NhanVien value) {
	list temp, p; //khai báo 2 list tạm
	temp = creatList(value);//gọi hàm creatList để khởi tạo list temp có next trỏ tới NULL và data là value
	if (l == NULL) {
		l = temp;
	}
	else {
		p = l;//khởi tạo p trỏ tới l
		while (p->next != NULL) {
			p = p->next;//duyệt đến cuối.list cuối là list có next = null
		}
		p->next = temp;//gán next của list cuối = temp,khi đó temp sẽ là list cuối(temp.next=NULL)
	}
	return l;
}
list addEmp(list l, NhanVien value, int position) {
	if (position == 0 || l == NULL) {
		l = addl(l, value);//nếu vị trí chèn = 0, => thêm vào đầu
	}
	else {
		//bắt đầu tìm vị trí cần chèn. dùng k để đếm vị trí
		int k = 1;
		list p = l;
		while (p->next != NULL && k != position) {
			p = p->next;
			k++;
		}
		if (k != position) {
			//nếu duyệt hết danh sách mà vẫn chưa đến vị trí cần chèn, mặc định chèn cuối
			//nếu k muốn chèn, thông báo vị trí không hợp lệ
			l = addTail(l, value);
			//wcout<<"Vi tri chen vuot qua vi tri cuoi cung"<<endl;
		}
		else {
			list temp = creatList(value);
			temp->next = p->next;
			p->next = temp;
		}
	}
	return l;
}
list Dell(list l) {
	if (l == NULL) {
		wcout << L"DANH SÁCH RỖNG!!!";
	}
	else
	{
		l = l->next;
	}
	return l;
}
list dellTail(list l) {
	list p = l;
	while (p->next->next != NULL) {
		p = p->next;
	}
	p->next = p->next->next;//cho next = NULL
							//hoặc p->next  = NULL
	return l;
}
list DelAt(list l, int position) {
	if (position == 0 || l == NULL) {
		l = Dell(l); //nếu vị trí chèn = 0,Xoá đầu
	}
	else {
		//tìm vị trí chèn. dùng k để đếm vị trí
		int k = 1;
		list p = l;
		while (p->next->next != NULL && k != position)
		{
			p = p->next;
			++k;
		}
		if (k != position) {
			//nếu duyệt hết danh sách mà không tìm được vị trí cần xoá, mặc định xoá cuối
			//nếu k muốn xoá,thông báo vị trí xoá k hợp lệ
			l = dellTail(l);
		}
		else {
			p->next = p->next->next;
		}
	}
	return l;
}
NhanVien Get(list l, int index) {
	int k = 0;
	list p = l;
	while (p != NULL && k != index) {
		p = p->next;
		++k;
	}
	return p->data;
}
int search(list l, NhanVien value) {
	int pos = 0;
	for (list p = l; p != NULL; p = p->next)
	{
		if (p->data == value)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}
int search(list l, NhanVien value, float hsl) {
	int pos = 0;
	for (list p = l; p != NULL; p = p->next)
	{
		if (p->data == value && p->data.getHeSoLuong() == hsl)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}
int search2(list l, wstring value) {
	int pos = 0;
	for (list p = l; p != NULL; p = p->next)
	{
		Date ns = outputBOD(value);
		if (p->data.getHoTen() == value)
		{
			return pos;
		}
		else if (p->data.getChucVu() == value)
		{
			return pos;
		}
		else if (p->data.getNgaySinh().ngay == ns.ngay
			|| p->data.getNgaySinh().thang == ns.thang
			|| p->data.getNgaySinh().nam == ns.nam)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}
list DelByVal(list l, NhanVien value) {
	int pos = search(l, value);
	while (pos != -1) {
		DelAt(l, pos);
		pos = search(l, value);
	}
	return l;
}
bool findString(const wstring str1, const wstring str2) {
	int i = 0, save, temp, size1;
	wstring s1 = toLower(str1);
	wstring s2 = toLower(str2);
	int size2 = str2.length();
	while (s1[i] != '\0') {//LẬP CHUỖI DÀI
		if (s1[i] == s2[0]) {//KT PHẦN TỬ 1 CỦA CHUỖI 2 CÓ BẰNG PHẦN TỬ thứ i CỦA CHUỖI 1
			int j = 1;
			save = i;
			temp = i;//LƯU VỊ TRÍ KHI I = PHẦN TỬ 1 CỦA CHUỖI 2
			size1 = 1;//LƯU LẠI KÍCH THƯỚC CỦA CHUỖI 1(PHẦN TRÙNG VỚI CHUỖI 2)
			while ((s2[j] != '\0' || s1[save + 1] != '\0') && s1[save + 1] == s2[j]) {
				j++;
				save++;
				size1++;
			}
			if (s2[j] == '\0' && size2 == size1)
				return true;
			else {
				i = temp;
				i++;
			}
		}
		else i++;
	}
	return false;
}
bool findString(const Date ns1, const wstring subString) {

	if (ns1.ngay == StringToInt(subString) || ns1.thang == StringToInt(subString) || ns1.nam == StringToInt(subString))
		return true;
	else return false;
}
list dellByString(list l, wstring subString) {
	for (list p = l; p != NULL; p = p->next)
	{
		if (findString(p->data.getHoTen(), subString))
		{
			int pos = search(l, p->data);
			l = DelAt(l, pos);
		}
		else if (findString(p->data.getChucVu(), subString))
		{
			int pos = search(l, p->data);
			l = DelAt(l, pos);
		}
		else if (findString(p->data.getNgaySinh(), subString))
		{
			int pos = search(l, p->data);
			l = DelAt(l, pos);
		}
		else if (p->data.getHeSoLuong() == StringToFloat(subString))
		{

			int pos = search(l, p->data, StringToFloat(subString));
			l = DelAt(l, pos);
		}
	}
	return l;
}
int searchByString(list l, list p, wstring subString) {
	if (findString(p->data.getHoTen(), subString))
	{
		int pos = search(l, p->data);
		return pos;
	}
	else if (findString(p->data.getChucVu(), subString))
	{
		int pos = search(l, p->data);
		return pos;
	}
	else if (findString(p->data.getNgaySinh(), subString))
	{
		int pos = search(l, p->data);
		return pos;
	}
	
	else if (p->data.getHeSoLuong() == StringToFloat(subString))
	{

		int pos = search(l, p->data, StringToFloat(subString));
		return pos;
	}
	return -1;
}
void displayEmp(list l, wstring sub) {
	int flag = 0;
	for (list p = l; p != NULL; p = p->next)
	{
		int i = searchByString(l, p, sub);
		if (i != -1) {
			flag++;
			NhanVien value = Get(l, i);
			wcout << background('-', 118) << endl;
			wcout << L"STT: " << i + 1 << endl;
			wcout << L"Họ tên : " << value.getHoTen() << endl;
			wcout << L"Chức vụ : " << value.getChucVu() << endl;
			wcout << L"Ngày sinh : " << BODtoSTR(value.getNgaySinh()) << endl;
			wcout << L"Hệ số lương : " << fixed << setprecision(3) << value.getHeSoLuong() << endl;

		}
	}
	if (flag == 0) {
		wcout << "====================" << endl;
		wcout << L"KHÔNG TÌM THẤY" << endl;
		wcout << "====================" << endl;
	}
}
void setInfo(list l) {
	wcout << endl;
	int i = 0;
	wcout << background(L'_', 118) << endl;
	wcout << background(L"STT", 10) << "|";
	wcout << background(L"Họ và tên", 25) << "|";
	wcout << background(L"Chức vụ", 25) << "|";
	wcout << background(L"Ngày tháng năm sinh", 25) << "|";
	wcout << L"Hệ số lương" << endl;
	for (list p = l; p != NULL; p = p->next)
	{
		wcout << background(IntToString(i + 1), 10) << "|";
		wcout << background(p->data.getHoTen(), 25) << "|";
		wcout << background(p->data.getChucVu(), 25) << "|";
		wcout << background(BODtoSTR(p->data.getNgaySinh()), 25) << "|";
		wcout << fixed << setprecision(3) << p->data.getHeSoLuong() << endl;
		++i;
	}
	wcout << background('_', 118) << endl;
}
list Initl() {
	list l;
	l = NULL;
	return l;
}
int Length(list l) {
	int len = 0;
	for (list p = l; p != NULL; p = p->next)
	{
		++len;
	}
	return len;
}
list Input(NhanVien value) {
	list l = Initl();
	/*int n;
	NhanVien value;*/
	//do {
	//	/*wcout << "Nhập số nhân viên: ";
	//	wcin >> n;*/
	//	
	//} while (n <= 0);
	//for (int i = 0; i < n; i++)
	//{
	//	/*wcout << "Nhap gia tri can them: ";
	//	wcin >> value;*/
	//	l = addTail(l, value);
	//}
	l = addTail(l, value);
	return l;
}


list input(wfstream &file, list l) {

	
	std::locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	file.imbue(loc);
	wstring info;

	getline(file, info);
	while (getline(file, info)) {
		wstring* ptr = new wstring[4];
		ptr = Split(info, ',');
		wstring hoten = *(ptr);
		wstring chucvu = *(ptr + 1);
		Date Date = outputBOD(*(ptr + 2));
		float hsl = (float)StringToFloat(*(ptr + 3));
		NhanVien* nhanvien = new NhanVien(hoten, chucvu, Date, hsl);
		l = addTail(l, *nhanvien);
	}
	file.close();
	return l;
}
list outPutList(list l, wstring name) {
	wfstream _file;

	_file.open(name, ios::out);
	std::locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	_file.imbue(loc);
	_file << background(L"STT", 10)
		<< background(L"Họ và tên", 25)
		<< background(L"Chức vụ", 25)
		<< background(L"Ngày tháng năm sinh", 25)
		<< background(L"Hệ số lương", 25)
		<< "\n";
	int i = 1;
	for (list p = l; p != NULL; p = p->next)
	{
		float num = p->data.getHeSoLuong();
		_file << background(IntToString(i), 10)
			<< background(p->data.getHoTen(), 25)
			<< background(p->data.getChucVu(), 25)
			<< background(BODtoSTR(p->data.getNgaySinh()), 25)
			<< fixed << setprecision(3)
			<< num
			<< "\n";
		i++;
	}
	wcout << L"XUẤT FILE THÀNH CÔNG!!!" << endl;
	_file.close();
	return l;
}
bool compareDate(const Date d1, const Date d2) {

	int ngay1 = d1.ngay;
	int ngay2 = d2.ngay;
	int thang1 = d1.thang;
	int thang2 = d2.thang;
	int nam1 = d1.nam;
	int nam2 = d2.nam;
	if (nam1 < nam2) {
		return true;
	}
	if (nam1 == nam2 && thang1 < thang2) {
		return true;
	}
	if (nam1 == nam2 && thang1 == thang2 && ngay1 < ngay2) {
		return true;
	}
	return false;
}
bool compareSalary(float d1, float d2) {
	if (d1 <= d2) {
		return true;
	}
	else return false;
}
int getPosition(const wstring str) {
	wstring temp = toLower(str);

	wstring ct = L"chủ tịch";
	wstring pct = L"phó chủ tịch";
	wstring gd = L"giám đốc";
	wstring pgd = L"phó giám đốc";
	wstring tk = L"thư ký";
	wstring tp = L"trưởng phòng";
	wstring pp = L"phó phòng";
	wstring nv = L"nhân viên";
	wstring tt = L"thực tập";
	int x = 0;

	if (equal(temp, ct))  x = 10;
	else if (equal(temp, pct))  x = 9.5;
	else if (equal(temp, gd))  x = 9;
	else if (equal(temp, pgd))  x = 8.5;
	else if (equal(temp, tp))  x = 7;
	else if (equal(temp, pp))  x = 6.5;
	else if (equal(temp, tk))  x = 5;
	else if (equal(temp, nv))  x = 4;
	else if (equal(temp, tt))  x = 3;
	return x;
}
bool comparePosition(const wstring d1, const wstring d2) {
	int x = getPosition(d1);
	int y = getPosition(d2);
	if (x <= y)return true;
	else return false;
}
bool compareName(wstring d1, wstring d2) {
	wstring s1 = toUpper(d1);
	wstring s2 = toUpper(d2);
	wstring* str1 = Split(s1, ' ');
	wstring* str2 = Split(s2, ' ');
	int p1 = 0;
	int p2 = 0;
	while (*(str1 + p1) != L"\0") {
		++p1;
	}
	while (*(str2 + p2) != L"\0")
	{
		++p2;
	}
	int i = 0;
	int j = 0;
	while ((*(str1 + p1 - 1))[i] != '\0' && (*(str2 + p2 - 1))[j] != '\0')
	{
		if ((*(str1 + p1 - 1))[i] == (*(str2 + p2 - 1))[j]) { i++; j++; }
		else if ((*(str1 + p1 - 1))[i] > (*(str2 + p2 - 1))[j]) return false;
		else if ((*(str1 + p1 - 1))[i] < (*(str2 + p2 - 1))[j]) return true;
	}
	return false;
	/*return false;*/
}

list combined(list a, list b, int thutu, int type) {
	list result = NULL;

	//Base case
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	//chọn a hoặc b, và đệ qui
	if (type == 0) { //TÊN
		if (thutu == 1) {
			if (compareName(a->data.getHoTen(), b->data.getHoTen())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}
		else {
			if (!compareName(a->data.getHoTen(), b->data.getHoTen())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}
	}
	if (type == 1) { //CHỨC VỤ
		if (thutu == 1) {
			if (comparePosition(a->data.getChucVu(), b->data.getChucVu())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}
		else {
			if (!comparePosition(a->data.getChucVu(), b->data.getChucVu())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}
	}
	if (type == 2) { //NGÀY SINH
		if (thutu == 1) {
			if (compareDate(a->data.getNgaySinh(), b->data.getNgaySinh())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}
		else {
			if (!compareDate(a->data.getNgaySinh(), b->data.getNgaySinh())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}

	}
	if (type == 3) { //HỆ SỐ LƯƠNG
		if (thutu == 1) {
			if (compareSalary(a->data.getHeSoLuong(), b->data.getHeSoLuong())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}
		else {
			if (!compareSalary(a->data.getHeSoLuong(), b->data.getHeSoLuong())) {
				result = a;
				result->next = combined(a->next, b, thutu, type);
			}
			else {
				result = b;
				result->next = combined(a, b->next, thutu, type);
			}
		}
		return result;
	}


	return result;
}
int checkType(wstring info) {
	if (equal(toLower(info), L"ho va ten")
		|| equal(toLower(info), L"ten")
		|| equal(toLower(info), L"hovaten")
		|| equal(toLower(info), L"ho ten")
		|| equal(toLower(info), L"hoten")
		|| equal(toLower(info), L"họ và tên")
		|| equal(toLower(info), L"tên")
		) {
		return 0;
	}
	if (equal(toLower(info), L"chuc vu") || equal(toLower(info), L"chức vụ")
		|| equal(toLower(info), L"chucvu")) {
		return 1;
	}
	if ((equal(toLower(info), L"ngay thang nam sinh"))
		|| (equal(toLower(info), L"ngay thang nam"))
		|| (equal(toLower(info), L"ngay sinh"))
		|| (equal(toLower(info), L"ngày tháng năm sinh"))
		|| (equal(toLower(info), L"ngày tháng năm"))
		|| (equal(toLower(info), L"ngày tháng"))
		|| (equal(toLower(info), L"ngaythangnamsinh"))
		|| (equal(toLower(info), L"ngaysinh")))
	{
		return 2;
	}
	if (equal(toLower(info), L"luong") || equal(toLower(info), L"he so luong") || equal(toLower(info), L"lương") || equal(toLower(info), L"hệ số lương")
		|| (equal(toLower(info), L"hesoluong"))) {
		return 3;
	}
	return -1;
}
void frontBackSplit(list source, list* frontRef, list* backRef) {
	list f;
	list s;
	s = source;
	f = source->next;
	//di chuyển f 2 list,di chuyển s 1 list
	while (f != NULL)
	{
		f = f->next;
		if (f != NULL)
		{
			s = s->next;
			f = f->next;
		}
	}
	//chia danh sách làm 2
	*frontRef = source;
	*backRef = s->next;
	s->next = NULL;
}
void mergeSort(list* lRef, int thutu, int type) {
	list l = *lRef;
	list a;
	list b;

	//Length = 0 hoặc 1
	if ((l == NULL) || (l->next == NULL)) {
		return;
	}
	//Split l into 'a' and 'b' sublist
	frontBackSplit(l, &a, &b);
	/* Recursively sort the sublists */
	mergeSort(&a, thutu, type);
	mergeSort(&b, thutu, type);
	//answer=merge the two sorted list together
	*lRef = combined(a, b, thutu, type);
}
void sortList(list* lRef) {
	list l = *lRef;
	int choose;
	wstring input;
	wcin.ignore();
	wcout << background('*', 118) << endl;
	wcout << L"TIÊU CHÍ SẮP XẾP: " ;
	getline(wcin, input);
	int type = checkType(input);
	if (type == -1) {
		wcout << L"LỖI CÚ PHÁP!!!";
		return;
	}
	wcout << L"THỨ TỰ SẮP XẾP: \n" ;
	wcout << L"1.TĂNG DẦN \n";
	wcout << L"2.GIẢM DẦN \n";
	wcin >> choose;
	wcout << L"Chọn: " << choose;
	if (choose == 1) {
		mergeSort(lRef, 1, type);
	}
	else
	{
		mergeSort(lRef, 2, type);
	}
}
list addEmp(list l) {
	wcin.ignore();
	wstring ht;
	wstring cv;
	wstring ns;
	float hsl;
	int pos;
	wcout << background('+', 118) << endl;
	wcout << L"HỌ VÀ TÊN: ";
	getline(wcin, ht);
	wcout << L"CHỨC VỤ: ";
	getline(wcin, cv);
	wcout << L"NGÀY THÁNG NĂM SINH: ";
	getline(wcin, ns);
	wcout << L"HỆ SỐ LƯƠNG: ";
	wcin >> hsl;
	wcout << L"VỊ TRÍ MUỐN CHÈN VÀO: ";
	wcin >> pos;
	wcout << background('+', 118) << endl;
	Date Date = outputBOD(ns);
	NhanVien nv = NhanVien(ht, cv, Date, hsl);
	l = addEmp(l, nv, pos - 1);
	return l;

}
list dellEmp(list l) {
	wcin.ignore();
	wstring s;
	wcout << background('+', 118) << endl;
	wcout << L"NHẬP CHUỖI CẦN XOÁ: \n";
	getline(wcin, s);
	wcout << background('+', 118) << endl;
	l = dellByString(l, s);
	return l;
}
void Display(list l) {
	wcin.ignore();
	wstring s;
	wcout << background('+', 118) << endl;
	wcout << L"NHẬP CHUỖI TÌM KIẾM: \n";
	getline(wcin, s);
	wcout << background('+', 118) << endl;
	displayEmp(l, s);
}
int main()
{
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	HANDLE hdlConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX consoleFont;
	consoleFont.cbSize = 16;
	GetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);
	memcpy(consoleFont.FaceName, L"Consolas", sizeof(consoleFont.FaceName));
	SetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);

	wfstream file;
	wstring info;
	int n ;
	std::locale loc(locale(), new codecvt_utf8<wchar_t>);  // UTF-8
	//file.imbue(loc);
	wcout << background('*', 118) << endl;
	file.open("input.txt", ios::in);
	list l = Initl();
	l = input(file, l);
	setInfo(l);

	while (true) {
		wcout << L" \n\n\t\t BẠN MUỐN LÀM GÌ? \n";
		wcout << L"1.SẮP XẾP NHÂN VIÊN THEO TIÊU CHÍ, THỨ TỰ \n";
		wcout << L"2.THÊM NHÂN VIÊN VÀO VỊ TRÍ \n";
		wcout << L"3.XOÁ NHÂN VIÊN THEO TỪ KHOÁ \n";
		wcout << L"4.TÌM NHÂN VIÊN THEO TỪ KHOÁ \n";
		wcout << L"5.XUẤT DANH SÁCH \n";
		wcout << L"0.THOÁT \n\n";
		wcout << background('*', 118) << endl;
		n = getIntRange(0, 5);
		switch (n) {
		case 0:
			return 0;
			break;
		case 1:
			sortList(&l);
			setInfo(l);
			break;
		case 2:
			l = addEmp(l);
			sortList(&l);
			setInfo(l);
			break;
		case 3:
			l = dellEmp(l);
			setInfo(l);
			break;
		case 4:
			Display(l);
			break;
		case 5:
			wcin.ignore();
			wstring add;
			wcout << background('~', 118) << endl;
			wcout << L"NHẬP ĐỊA CHỈ: ";
			getline(wcin, add);
			outPutList(l, add);
			wcout << background('~', 118) << endl;
		}
	}
	std::system("pause");
	return 0;
}