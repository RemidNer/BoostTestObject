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
	//shared_ptr、make_shared的使用，避免使用new、delete造成的内存问题
	boost::shared_ptr<std::string> ps = boost::make_shared<std::string>(", I made a stupid decision to leave the world forever");
	std::cout << "The ps content is: " << *ps << std::endl;
}

void case2()
{
	//to_replace_first()
	std::string str("ReadMe.txt");
	if (boost::ends_with(str, "txt"))								//判断后缀
	{
		std::cout << boost::to_upper_copy(str) + " UPPER" << std::endl;
		assert(boost::ends_with(str, "txt"));
	}

	boost::replace_first(str, "ReadMe", "followme");				//替换原字符串内容
	cout << "The replace_first str content: " << str << endl;

	vector<char> v(str.begin(), str.end());							//一个字符大小的vector
	vector<char> v2 = to_upper_copy(erase_first_copy(v, "txt"));	//to_upper_copy大写，然后删除字符串

	/*
	for (int i = 0; i < v2.size(); ++i)
	{
		cout << v2[i];
	}*/
	for (auto tmp : v2)												//此种方式虽较为方便，但是比起前++的常规for循环来说，开销较大
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

	assert(iends_with(str, "bomb"));		//大小写无关检测后缀
	assert(!ends_with(str, "bomb"));		//大小写敏感检测后缀
	assert(starts_with(str, "Pow"));		//检测前缀
	assert(contains(str, "er"));			//测试包含关系
	
	string str2 = to_lower_copy(str);		//转换小写并返回一个拷贝
	assert(iequals(str, str2));				//大小写无关判断相等
	
	string str3 = "power suit";
	assert(lexicographical_compare(str, str3));//大小写无关比较

	assert(all(str2.substr(0, 5), is_lower()));//检测子串均小写
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
	cout << "Delete Both Spaces: " << fmt % trim_copy(str) << endl;	//删除两端的空格
	cout << "Delete Left Space : " << fmt % trim_left_copy(str) << endl;//删除左边的空格
	cout << "Delete Right Space: " << fmt % trim_right_copy(str) << endl;//删除右边的空格

	trim_right(str);										//原地删除右边的空格
	cout << "In Situ Delete: " << fmt % str << endl;

	string str1 = "2017 is a year of egg pain;";
	cout << "Delete Left Nums: " << fmt % trim_left_copy_if(str1, is_digit());		//删除左端的数字
	cout << "Delete Right put: " << fmt % trim_right_copy_if(str1, is_punct());		//删除有段的标点
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

	typedef find_iterator<string::iterator> string_find_iterator;	//查找迭代器类型定义

	string_find_iterator pos, end;									//声明查找迭代器变量
	for (pos = make_find_iterator(str,first_finder("samus",is_iequal()));pos != end;++pos)
	{
		cout << "Pos Content is: " << *pos << ";";
	}
	cout << endl;

	typedef split_iterator<string::iterator> string_split_iterator;	//分割迭代器类型定义

	string_split_iterator p, endp;									//声明分割迭代器变量
	for (p = make_split_iterator(str,first_finder("||",is_iequal()));p != endp;++p)	//is_iequal()判断是否相等
	{
		cout << "P Content is: " << *p << ";";
	}
	cout << endl;
}

void case13()
{
	//tokenizer<> tok(std::string);
	string str = "Link raise the master-sword.";

	tokenizer<> tok(str);			//使用缺省模版参数创建分词对象
									//此时是默认使用空格、标点符号进行字符分词

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