#include <iostream>
#include "Header.h"

using namespace std;

//prototypes 
struct end_nodes; class VAK; class GG;
void Afdrukken(VAK* ingang);



int power(int a, int p) {
	int n = 1;
	for (int i = 0; i < p; i++) {
		n = n*a;
	} return n;
}


void GG::create_forwards(end_nodes &in,int a) {
	VAK* new_ = new VAK;
	if (!in.yet_created){
		in.eind = new_;
	}
	else {
		in.begin->prev = new_;
	}
	new_->next = in.begin;
	new_->N = a;
	new_->int_to_array(*new_);
	in.begin = new_;
}
void GG::create_backwards(end_nodes &in, int a) {
	VAK* new_ = new VAK;
	if (!in.yet_created) {
		in.begin = new_;
		in.yet_created = true;
	}
	else {
		in.eind->next = new_;
	}
	new_->next = nullptr;
	new_->prev = in.eind;
	new_->N = a;
	new_->int_to_array(*(new_));
	in.eind = new_;
}
void GG::addition(end_nodes A, end_nodes B) {
	VAK* aa = A.eind;
	VAK* bb = B.eind;
	int carry_over = 0;
	while ((aa != nullptr || bb != nullptr)&&(aa!=bb)) {
		int a = 0; int b = 0;
		if (aa != nullptr) {
			a = aa->N;
		} if (bb != nullptr) {
			b = bb->N;
		}
		int i = a + b + carry_over;
//		cout << "i =   " << i << "    " << i % power(10 ,k) << "    " << carry_over << endl;
		create_forwards(C, i % power(10, k));
		carry_over = i / power(10, k);
		if (aa!=nullptr) aa = aa->prev;
		if (bb!=nullptr) bb = bb->prev;
	} if (carry_over!=0) create_forwards(C, carry_over);
}
void GG::single_multiplication(VAK* v,end_nodes n) {
	VAK* h = n.begin;
	while (h != nullptr) {
		create_backwards(C, (v->N*h->N));
		h = h->next;
	} cout << endl << endl;
}
/*
void GG::many_mult(vak* v) {
	vak* h = v;
	int scooch_over = 0;
	while (h != nullptr) {

		single_multiplication(h, B);
		addition();
		h = h->next;
		scooch_over++;
	} 
}*/
void GG::construct_GG() {
	number_length = 0; exit = false;
}
void Afdrukken(VAK* ingang) {
	int* p;
	if (ingang != nullptr) {
		VAK* hulp = ingang;
		while (hulp != nullptr) {
			p = &hulp->A[0];
			for (int a = 0; a < 4; a++) {
				cout << *p;
				p++;
			} cout << ' ';
			hulp = hulp->next;
		} cout << endl << endl;
	}
}
void GG::fill_GG(end_nodes &in) {
	char input = cin.get(); 				 
	int total_length = 0;
	int n = 0;
	if (input == '\n') { fill_GG(in); }
	if (input == '0') { fill_GG(in); }
	while (input != '\n') {
		if (isdigit(input)) {
			number_length++;
			total_length++;
			n = n * 10 + (input - '0');
			if (number_length == k) {
				create_backwards(in, n);
				number_length = 0;
				n = 0;
			}
		} input = cin.get();
	} if (n != 0) create_backwards(in, n);
	VAK v; 
	if (number_length!=0) v.re_arrange(number_length ,in);
	number_length = 0;
}
void VAK::re_arrange(int n, end_nodes N) {
	VAK* h = N.eind;
	if (h->prev == nullptr) return;
	h->N += (h->prev->N % power(10, k-n))*power(10, n);
	int_to_array(*h);
	h = h->prev;
	while (h->prev != nullptr) {
		int a = h->N;
		h->N = 0;
		h->N += a / power(10, n);
		h->N += (h->prev->N % power(10, k - n))*power(10, n);
		int_to_array(*h);
		h = h->prev;
	}
	h->N /= power(10, k-n);
	int_to_array(*h);
}
void GG::menu() {
	char input = cin.get();
	switch (input) {
	case 'a': {
		addition(A, B);
		break;
	}
	case 'm': {
		cout << "C:" << endl;
		single_multiplication(A.begin, B);
		Afdrukken(C.begin);
		break;
	}
	case 'p': {
		char c;
		cout << "A or B" << endl;
		cin >> c;
		switch (c) {
		case 'a':
			fill_GG(A); break;
		case 'b':
			fill_GG(B); break;
		}

		cout << "A:" << endl;
		Afdrukken(A.begin);
		cout << "B:" << endl;
		Afdrukken(B.begin);
		break;
	}
/*	case 'f':{
		int i;
		cin >> i;
		create_forwards(C, i);
		Afdrukken(C.begin);
		break;
*///	}
		case 'x':
			exit = true;
	}
}

int main() {
	GG g;
	g.construct_GG();
	while (!g.exit) {
		cout << "[p]ut in || e[x]it" << endl;
		g.menu();
	}
	cin.get();
}