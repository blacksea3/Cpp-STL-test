#include "../public/public.hpp"
#include "../mLib/mLibBinaryTree.hpp"

/*
 * 生成测试数据放入文本文件
 * 目标结果: 每次两个数字第一个是操作, 第二个是参数, 都是int
 * 输入: opStart:操作数字开始, opEnd操作数字结束,
 * paraStart参数开始, paraEnd参数结束, nums操作数量
 * filename:文件名
 * 
 * 注意: nums应当小于等于插入数据容量总数的一半
 * 
 * 针对二叉树设计, 目标结果: 操作:1插入 参数是值, 2删除 参数是值(有一半可能性是删除已经存在的值), 
 *    3打印, 参数是0(但不起作用), 4验证二叉树是否合法, 参数是0(但不起作用)
 * 
 */
void genTestDataBinaryTree(int opStart, int opEnd, int paraStart, int paraEnd, int nums, std::string filename)
{
	assert(nums <= (paraEnd - paraStart + 1) / 2);

	fstream fout(filename, std::ios::out);

	vector<int> pre;

	for (int i = 0; i < nums; ++i)
	{
		int opR = rand() % (opEnd - opStart + 1) + opStart;
		switch (opR)
		{
		case 1:
		{
			int paraR = rand() % (paraEnd - paraStart + 1) + paraStart;
			fout << 1 << " " << paraR << endl;
			pre.emplace_back(paraR);
			break;
		}
		case 2:
		{
			int isDelOccur = rand() % 2;
			if (isDelOccur == 0 || pre.empty())
			{
				while (true)
				{
					int paraR = rand() % (paraEnd - paraStart + 1) + paraStart;
					if (find(pre.begin(), pre.end(), paraR) == pre.end())
					{
						fout << 2 << " " << paraR << endl;
						break;
					}
				}
			}
			else
			{
				while (true)
				{
					int paraR = rand() % (paraEnd - paraStart + 1) + paraStart;
					vector<int>::iterator iter = find(pre.begin(), pre.end(), paraR);
					if (iter != pre.end())
					{
						fout << 2 << " " << paraR << endl;
						pre.erase(iter);
						break;
					}
				}
			}
			break;
		}
		case 3:
		{
			fout << 3 << " " << 0 << endl;
			break;
		}
		case 4:
		{
			fout << 4 << " " << 0 << endl;
		}
		default:
			break;
		}
	}
	fout.close();
}

/*
 * 生成测试数据结果放入文本文件
 * 用库函数的set测试
 * 输入: (in/out)filename:文件名
 */
void genOutputDataBinaryTree(std::string infilename, std::string outfilename)
{
	fstream fin;
	fin.open(infilename, std::ios::in);
	if (!fin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream fout;
	fout.open(outfilename, std::ios::out);
	if (!fout.is_open())
	{
		fin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	set<int> s;
	int op, para;
	while (fin >> op >> para)
	{
		switch (op)
		{
		case 1:
		{
			if (s.find(para) == s.end())
			{
				fout << 1 << endl;
				s.insert(para);
			}
			else
			{
				fout << 0 << endl;
			}
			break;
		}
		case 2:
		{
			if (s.find(para) == s.end())
			{
				fout << 0 << endl;
			}
			else
			{
				s.erase(para);
				fout << 1 << endl;
			}
			break;
		}
		case 3:
		{
			fout << s.size() << " ";
			for (auto& iters : s) fout << iters << " ";
			fout << endl;
			break;
		}
		case 4:
		{
			fout << 1 << endl;
		}
		default:
			break;
		}
	}
	fin.close();
	fout.close();
}

/*
 * 测试自定义二叉搜索树
 * 生成测试数据放入文本文件, 外部接口
 */
void genTestDataBinarySearchTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		genTestDataBinaryTree(1, 3, 0, 10000, 3 * (int)pow(2, i), fileName);
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		genOutputDataBinaryTree(fileName, outName);
	}
}

/*
 * 测试自定义AVL树
 * 生成测试数据放入文本文件, 外部接口
 */
void genTestDataAVLTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		genTestDataBinaryTree(1, 4, 0, 10000, 3 * (int)pow(2, i), fileName);
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		genOutputDataBinaryTree(fileName, outName);
	}
}

/*
 * 测试自定义二叉搜索树
 * 输入: (in/out)filename:文件名
 */
void testBinarySearchTree(std::string infilename, std::string outfilename)
{
	fstream finin;  //覆盖全局std:cin
	finin.open(infilename, std::ios::in);
	if (!finin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream foutin;
	foutin.open(outfilename, std::ios::in);
	if (!foutin.is_open())
	{
		finin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	mLib::mbinary_searchtree<int> nmbs;
	//mLib::nmbinary_searchtree<int> nmbs;
	int op, para;
	int count = 0;
	while (finin >> op >> para)
	{
		count++;
		int testRes = nmbs.checkIfTreeValid();
		assert((1 == testRes));
		switch (op)
		{
		case 1:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = nmbs.insert(para);
			assert(rightRes == testRes);
			break;
		}
		case 2:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = nmbs.remove(para);
			assert(rightRes == testRes);
			break;
		}
		case 3:
		{
			int rsize;
			foutin >> rsize;
			vector<int> rightRes(rsize);
			for (int i = 0; i < rsize; ++i) foutin >> rightRes[i];
			vector<int> testRes = nmbs.inorder();
			assert(rightRes == testRes);
			break;
		}
		default:
			break;
		}
	}

	finin.close();
	foutin.close();
}

/*
 * 测试自定义二叉搜索树接口
 */
void TestBinarySearchTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		testBinarySearchTree(fileName, outName);
		std::cout << "binary_search tree Class insert/remove/inorder passed test case" << i <<  " !!!" << endl;
	}
}

/*
 * 测试自定义AVL树
 * 输入: (in/out)filename:文件名
 */
void testAVLTree(std::string infilename, std::string outfilename)
{
	fstream finin;  //覆盖全局std:cin
	finin.open(infilename, std::ios::in);
	if (!finin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream foutin;
	foutin.open(outfilename, std::ios::in);
	if (!foutin.is_open())
	{
		finin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	mLib::mAVLtree<int> mAVL;
	//mLib::nmAVLTree<int> mAVL;
	int op, para;
	int count = 0;
	while (finin >> op >> para)
	{
		count++;
		int testRes = mAVL.checkIfAVLValid();
		assert((1 == testRes));
		switch (op)
		{
		case 1:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mAVL.insert(para);
			assert(rightRes == testRes);
			break;
		}
		case 2:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mAVL.remove(para);
			assert(rightRes == testRes);
			break;
		}
		case 3:
		{
			int rsize;
			foutin >> rsize;
			vector<int> rightRes(rsize);
			for (int i = 0; i < rsize; ++i) foutin >> rightRes[i];
			vector<int> testRes = mAVL.inorder();
			assert(rightRes == testRes);
			break;
		}
		case 4:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mAVL.checkIfAVLValid();
			assert((rightRes == 1) && (rightRes == testRes));
		}
		default:
			break;
		}
	}

	finin.close();
	foutin.close();
}

/*
 * 测试自定义AVL树接口
 */
void TestAVLTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		testAVLTree(fileName, outName);
		std::cout << "AVLtree Class insert/remove/inorder and its properity passed test case" << i << " !!!" << endl;
	}
}

/*
 * 测试自定义Splay树
 * 输入: (in/out)filename:文件名
 */
void testSplayTree(std::string infilename, std::string outfilename)
{
	fstream finin;  //覆盖全局std:cin
	finin.open(infilename, std::ios::in);
	if (!finin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream foutin;
	foutin.open(outfilename, std::ios::in);
	if (!foutin.is_open())
	{
		finin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	mLib::nmSplayTree<int> nsp;
	int op, para;
	int count = 0;
	while (finin >> op >> para)
	{
		count++;
		int testRes = nsp.checkIfTreeValid();
		assert((1 == testRes));
		switch (op)
		{
		case 1:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = nsp.insert(para);
			assert(rightRes == testRes);
			if (testRes == 1)
			{
				int testRes2 = nsp.checkIsSplayValid(para);
				assert((1 == testRes2));
			}
			break;
		}
		case 2:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = nsp.remove(para);
			assert(rightRes == testRes);
			break;
		}
		case 3:
		{
			int rsize;
			foutin >> rsize;
			vector<int> rightRes(rsize);
			for (int i = 0; i < rsize; ++i) foutin >> rightRes[i];
			vector<int> testRes = nsp.inorder();
			assert(rightRes == testRes);
			break;
		}
		default:
			break;
		}
	}

	finin.close();
	foutin.close();
}

/*
 * 测试自定义Splay树接口, 关于Splay树性质, 仅测试插入节点后那个节点是否移动到根部
 */
void TestSplayTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		testSplayTree(fileName, outName);
		std::cout << "SplayTree Class insert/remove/inorder and after insert root properity, passed test case" << i << " !!!" << endl;
	}
}

/*
 * 测试自定义RedBlack树
 * 输入: (in/out)filename:文件名
 */
void testRedBlackTree(std::string infilename, std::string outfilename)
{
	fstream finin;  //覆盖全局std:cin
	finin.open(infilename, std::ios::in);
	if (!finin.is_open())
	{
		throw std::exception("FATAL ERROR");
		return;
	}

	fstream foutin;
	foutin.open(outfilename, std::ios::in);
	if (!foutin.is_open())
	{
		finin.close();
		throw std::exception("FATAL ERROR");
		return;
	}

	mLib::mRedBlackTree<int> mrb;
	int op, para;
	int count = 0;
	while (finin >> op >> para)
	{
		count++;
		if (count == 421)
			int i = 1;
		switch (op)
		{
		case 1:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mrb.insert(para);
			assert(rightRes == testRes);
			testRes = mrb.checkIsRedBlackValid();
			assert((1 == testRes));
			break;
		}
		case 2:
		{
			int rightRes;
			foutin >> rightRes;
			int testRes = mrb.remove(para);
			assert(rightRes == testRes);
			testRes = mrb.checkIsRedBlackValid();
			assert((1 == testRes));
			break;
		}
		case 3:
		{
			int rsize;
			foutin >> rsize;
			vector<int> rightRes(rsize);
			for (int i = 0; i < rsize; ++i) foutin >> rightRes[i];
			vector<int> testRes = mrb.inorder();
			assert(rightRes == testRes);
			break;
		}
		default:
			break;
		}
	}

	finin.close();
	foutin.close();
}

/*
 * 测试自定义红黑树接口
 */
void TestRedBlackTreeInterface()
{
	std::string fileDir = "D:\\PC\\GitFiles\\Cpp-STL-test\\other\\CppAlgs\\TestData\\BinaryTreeTest";

	for (int i = 0; i < 10; ++i)
	{
		std::string fileName = fileDir + to_string(i) + ".txt";
		std::string outName = fileName.substr(0, fileName.size() - 4) + "res.txt";
		testRedBlackTree(fileName, outName);
		std::cout << "RedBlackTree Class insert/remove/inorder and its properity, passed test case" << i << " !!!" << endl;
	}
}
