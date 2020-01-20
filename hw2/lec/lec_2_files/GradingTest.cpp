#include "Grading.h"
#include <iostream>
#include <memory>
using namespace std;
using namespace mpcs51044;

int main()
{
	Student_info dave("David");
	dave.midterm = 76;
	dave.final = 97;
	cout << "Enter David's homework grades. One on each line. Negative to quit" << endl;
	dave.read(cin);
	cout << "David's grade is " << dave.grade() << endl;

	unique_ptr<Abstract_student_info> dmitriy = make_unique<BalancedGrading>("Dmitriy");
	dmitriy->midterm = 80;
	dmitriy->final = 100;
	cout << "Enter Dmitriy's homework grades. One on each line. Negative to quit" << endl;
	dmitriy->read(cin);
	cout << "Dmitriy's grade is " << dmitriy->grade() << endl;

	unique_ptr<Abstract_student_info> alexis = make_unique<IgnoreHomework>("Alexis");
	alexis->midterm = 80;
	alexis->final = 100;
	cout << "Enter Alexis' homework grades. One on each line. Negative to quit" << endl;
	alexis->read(cin);
	cout << "Alexis' grade is " << alexis->grade() << endl;

	auto lorenzo = make_unique<NewStudent_info>("Lorenzo", make_unique<BalancedGradingMachine>());
	lorenzo->midterm = 80;
	lorenzo->final = 100;
	cout << "Enter Lorenzo's homework grades. One on each line. Negative to quit" << endl;
	lorenzo->read(cin);
	cout << "Lorenzo's grade is " << lorenzo->grade() << endl;
	lorenzo->updateGradingMachine(make_unique<IgnoreHomeworkGradingMachine>());
	cout << "Now that grading policy is changed to ignore homework. Lorenzo's grade is "
		<< lorenzo->grade() << endl;

	return 0;
}