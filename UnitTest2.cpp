
#include "pch.h"
#include "CppUnitTest.h"
#include "../../3sem_aisd_lab2/AlgoritmShF.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		shannonfano test;
		
		TEST_METHOD(InsertAndFind)
		{
			test.insert('a');
			bool expected = true;
			bool inreal = false;
			if (test.find('a') != nullptr)
				inreal = true;
			Assert::AreEqual(inreal, expected);
		}

		TEST_METHOD(Remove)
		{
			test.insert('k');
			test.insert('l');
			test.insert('m');
			test.remove('m');
			bool expected = false, inreal = true;
			if (test.find('m')->symb != 'm')
				inreal = false;
			Assert::AreEqual(inreal, expected);
		}

		TEST_METHOD(PrintExeption)
		{
			try {
				test.Print();
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Tree is empty", msg);
			}
		}

		TEST_METHOD(ClearException)
		{
			try {
				test.clear();
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Tree is empty", msg);
			}
		}

		TEST_METHOD(RemoveException)
		{
			test.insert('t');
			test.insert('y');
			test.insert('a');

			try {
				test.remove('f');
			}
			catch (const char* msg)
			{
				Assert::AreEqual("There's no key like that", msg);
			}
		}

		TEST_METHOD(EncodingTest)
		{
			string quote = "Hello";
			int i = 0;
			while (i < quote.length())
			{
				test.insert(quote[i]);
				i++;
			}

			test.encoding_tree();

			bool expected = true, inreal = false;

			if (test.find('H')->code.get_front()->get_data() == false && test.find('H')->code.get_front()->get_next()->get_data() == true)
				if (test.find('e')->code.get_front()->get_data() == true && test.find('e')->code.get_front()->get_next()->get_data() == false)
					if (test.find('l')->code.get_front()->get_data() == true && test.find('l')->code.get_front()->get_next()->get_data() == true)
						if (test.find('o')->code.get_front()->get_data() == false && test.find('o')->code.get_front()->get_next()->get_data() == false)
							inreal = true;
			Assert::AreEqual(inreal, expected);

		}

		TEST_METHOD(EncodingException)
		{
			try {
				test.encoding_tree();
			}
			catch (const char* msg)
			{
				Assert::AreEqual("Tree is empty", msg);
			}
		}


		TEST_METHOD(DecodingTest)
		{
			string quote = "Hello";
			int i = 0;
			while (i < quote.length())
			{
				test.insert(quote[i]);
				i++;
			}

			test.encoding_tree();

			string todecode = "0110111100";;
			string decoded;
			test.decoding(todecode, decoded);
			Assert::AreEqual(decoded, quote);
		}
	};
}