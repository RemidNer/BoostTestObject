#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <list>								//for use lits<std::string> str
#include <boost/assign.hpp>					//for use list_of() function
#include <boost/format.hpp>					//for use format fmt("***")
#include <boost/tokenizer.hpp>				//for use tokenizer<> tok(std:;string)
#include <boost/smart_ptr.hpp>				//for use shared_ptr()
#include <boost/make_shared.hpp>			//for use make_shared()
#include <boost/typeof/typeof.hpp>			//for use BOOST_AUTO
#include <boost/algorithm/string.hpp>		//for use string_algo library

using namespace std;
using namespace boost;
using namespace boost::assign;

class TestPoint
{
public:
	TestPoint()
	{
		cout << "Class TestPoint Constructor" << endl;
	}

	void Show()
	{
		cout << "Class TestPoint Show Functions" << endl;
	}
	~TestPoint()
	{
	}
};

void case1()
{
	//shared_ptr��make_shared��ʹ�ã�����ʹ��new��delete��ɵ��ڴ�����
	boost::shared_ptr<std::string> ps = boost::make_shared<std::string>(", I made a stupid decision to leave the world forever");
	std::cout << "The ps content is: " << *ps << std::endl;
}

void case2()
{
	//to_replace_first()
	std::string str("ReadMe.txt");
	if (boost::ends_with(str, "txt"))								//�жϺ�׺
	{
		std::cout << boost::to_upper_copy(str) + " UPPER" << std::endl;
		assert(boost::ends_with(str, "txt"));
	}

	boost::replace_first(str, "ReadMe", "followme");				//�滻ԭ�ַ�������
	cout << "The replace_first str content: " << str << endl;

	vector<char> v(str.begin(), str.end());							//һ���ַ���С��vector
	vector<char> v2 = to_upper_copy(erase_first_copy(v, "txt"));	//to_upper_copy��д��Ȼ��ɾ���ַ���

	/*
	for (int i = 0; i < v2.size(); ++i)
	{
		cout << v2[i];
	}*/
	for (auto tmp : v2)												//���ַ�ʽ���Ϊ���㣬���Ǳ���ǰ++�ĳ���forѭ����˵�������ϴ�
	{
		cout << tmp;
	}
	cout << endl;
}

void case3()
{
	//to_upper_copy() & to_lower()
	string str("I Don't Know.\n");
	cout << "to_upper_copy: " << to_upper_copy(str) << endl;
	cout << "str Content: " << str << endl;

	to_lower(str);
	cout << "After lower str content: " << str << endl;
}

void case4()
{
	cout << "In case4() functions" << endl;
	//starts_with() & ends_with() & contains() & equals() & lexicographical_compare() & all()
	string str("Power Bomb");

	assert(iends_with(str, "bomb"));		//��Сд�޹ؼ���׺
	assert(!ends_with(str, "bomb"));		//��Сд���м���׺
	assert(starts_with(str, "Pow"));		//���ǰ׺
	assert(contains(str, "er"));			//���԰�����ϵ
	
	string str2 = to_lower_copy(str);		//ת��Сд������һ������
	assert(iequals(str, str2));				//��Сд�޹��ж����
	
	string str3 = "power suit";
	assert(lexicographical_compare(str, str3));//��Сд�޹رȽ�

	assert(all(str2.substr(0, 5), is_lower()));//����Ӵ���Сд
}

void case5()
{
	cout << "In case5() functions" << endl;
	//is_equal() & is_less() & is_not_greater()
	string str1 = "Samus", str2 = "samus";

	assert(!is_equal()(str1, str2));
	assert(is_less()(str1, str2));
}

void case6()
{
	//For Test class point use to shared ptr and make shared ptr
	boost::shared_ptr<TestPoint> t1 = boost::make_shared<TestPoint>();
	t1->Show();
}

void case7()
{
	//format & trim_copy & trim_left_copy & trim_right_copy & trim_left_copy_if & trim_right_copy_if & trim_copy_if
	format fmt("|%s|\n");

	string str = "   samus aran   ";
	cout << "Delete Both Spaces: " << fmt % trim_copy(str) << endl;	//ɾ�����˵Ŀո�
	cout << "Delete Left Space : " << fmt % trim_left_copy(str) << endl;//ɾ����ߵĿո�
	cout << "Delete Right Space: " << fmt % trim_right_copy(str) << endl;//ɾ���ұߵĿո�

	trim_right(str);										//ԭ��ɾ���ұߵĿո�
	cout << "In Situ Delete: " << fmt % str << endl;

	string str1 = "2017 is a year of egg pain;";
	cout << "Delete Left Nums: " << fmt % trim_left_copy_if(str1, is_digit());		//ɾ����˵�����
	cout << "Delete Right put: " << fmt % trim_right_copy_if(str1, is_punct());		//ɾ���жεı��
	cout << "Delete Both Nums & Punct & Spaces: " << fmt % trim_copy_if(str1, is_punct() || is_digit() || is_space());
}

void case8()
{
	//find_first & find_last & find_nth & find_head & find_tail
	format fmt("|%s| .Pos value is: %d\n");
	string str = "Long Long Ago,There Have A King;";

	iterator_range<string::iterator> rge;		//Explain the iterator interval
	rge = find_first(str, "Long");				//Find the location of the first occurrence with case
	cout << "Find First: " << setw(5) <<  fmt % rge % (rge.begin() - str.begin());

	rge = ifind_first(str, "Long");				//Case independent search for the first place to appear
	cout << "Ifind first: " << setw(5) << fmt % rge % (rge.begin() - str.begin());

	rge = find_nth(str, "ng", 2);				//Look for ng's third place in STR
	cout << "Find nth: " << setw(5) << fmt % rge % (rge.begin() - str.begin());

	rge = find_head(str, 4);					//Take the first four characters
	cout << "Find Head: " << setw(5) << fmt % rge % (rge.begin() - str.begin());

	rge = find_tail(str, 5);					//Take the last five characters
	cout << "Find Tail: " << setw(5) << fmt % rge % (rge.begin() - str.begin());

	rge = find_first(str, "samus");				//Not Find
	assert(rge.empty() && !rge);

}

void case9()
{
	//replace_*** & erase_***
	string str = "Samus beat the monster.\n";

	cout << "replace_first_copy: " << replace_first_copy(str, "Samus", "samus") << endl;;

	replace_last(str, "beat", "kill");
	cout << "replace_last: " << str << endl;

	cout << "ierase_all_copy: " << ierase_all_copy(str, "samus") << endl;
	cout << "replace_nth_copy: " << replace_nth_copy(str, "1", 1, "L") << endl;
	cout << "erase_tail_copy: " << erase_tail_copy(str, 8) << endl;
}

/*
void case10()
{
	string str = "Samus,Link.Zelda::Mario-Luigi+zelda";
	deque<string> d;

	ifind_all(d, str, "zELDA");		//Case-insensitive segmentation strings are not distinguishable
	assert(d.size() == 2);
	cout << "deque size: " << d.size() << endl;

	for (BOOST_AUTO(pos, d.begin());pos != d.end();++pos)
	{
		cout << "Pos:[ " << *pos << " ]";
	}
	cout << endl;

	list <iterator_range<string::iterator>> ls;
	split(ls, str, is_any_of(",.:-+"));	//Use punctuation marks
	for (auto tmp:ls)
	{
		cout << "Pos: [ " << tmp << " ]";
	}
	cout << endl;

	ls.clear();
	split(ls, str, is_any_of(".:-"), token_compress_on);
	for (auto tmp : ls)
	{
		cout << "Pos:[ " << tmp << " ];";
	}
	cout << endl;
}
*/

void case11()
{
	//list_of() & join() & join_if()
	vector<string> str = list_of("Samus")("Link")("Zelda")("Mario")("1234a5");	//initlazing vector
	cout << "Vector str size is: " << str.size() << endl;
	cout << "Vector str Content: " << join(str, "+") << endl;			//coalescing

	struct is_contains_a 
	{
		bool operator()(const string &st)
		{
			return contains(st, "a");
		}
	};
	cout << "After Operator() str Content: " << join_if(str, "**", is_contains_a()) << endl;	//coalescing
}

void case12()
{
	//find_iterator & make_find_iterator & split_iterator & make_split_iterator
	string str("Samus||samus||mario||||Link");

	typedef find_iterator<string::iterator> string_find_iterator;	//���ҵ��������Ͷ���

	string_find_iterator pos, end;									//�������ҵ���������
	for (pos = make_find_iterator(str,first_finder("samus",is_iequal()));pos != end;++pos)
	{
		cout << "Pos Content is: " << *pos << ";";
	}
	cout << endl;

	typedef split_iterator<string::iterator> string_split_iterator;	//�ָ���������Ͷ���

	string_split_iterator p, endp;									//�����ָ����������
	for (p = make_split_iterator(str,first_finder("||",is_iequal()));p != endp;++p)	//is_iequal()�ж��Ƿ����
	{
		cout << "P Content is: " << *p << ";";
	}
	cout << endl;
}

void case13()
{
	//tokenizer<> tok(std::string);
	string str = "Link raise the master-sword.";

	tokenizer<> tok(str);			//ʹ��ȱʡģ����������ִʶ���
									//��ʱ��Ĭ��ʹ�ÿո񡢱����Ž����ַ��ִ�

	for (BOOST_AUTO(pos,tok.begin());pos != tok.end();++pos)
	{
		cout << " Pos Content: " << *pos << endl;
	}
}

int main()
{
	case13();
	system("pause");
}