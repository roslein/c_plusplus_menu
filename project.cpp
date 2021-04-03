#include<iostream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct book
{
	int id; // 책 아이디
	char title[30]; // 책 제목
};

struct member
{
	int id; //학생 아이디
	char name[30]; // 학생이름
};
int main() 
{
	struct book books[10]; // 책 10개
	struct member members[5]; // 책 5개

	FILE* bookfp;
	FILE* memberfp;
	FILE* managefp;

	int menu;
	
	int book_append_id;
	char book_append_title[30];
	int member_append_id;
	char member_append_name[30];

	int book_modify_menu;
	int book_modify_id;
	char book_modify_title[30];
	
	int member_modify_menu;
	int member_modify_id;
	char member_modify_name[30];

	while (1)
	{
		cout << "menu: 1.quit 2.book show 3.book modify 4.book remove 5.add a book 6.member show" << endl;
		cout << "7.member modify 8.member remove 9.add a member 10.borrow 11.return" << endl;
		cin >> menu;

		switch (menu)
		{
		case 1: // quit
			cout << "you chose to quit";
			exit(1); // 모든 프로세스 종료
			break;

		case 2://book show
			bookfp = fopen("book.txt", "r");
			if (bookfp == NULL)
			{
				fprintf(stderr, "book file open error!");
				exit(1);
			}

			//fscanf(bookfp,"%id %title",)

			for (int i = 0; i < 10; i++)
			{
				fscanf(bookfp, "%d %s", &books[i].id, &books[i].title);
				if (feof(bookfp))
				{
					break;
				}
				cout << books[i].id << " " << books[i].title << endl;
			}

			fclose(bookfp);
			break;
		case 3: //book modify
			bookfp = fopen("book.txt", "r");

			if (bookfp == NULL)
			{
				fprintf(stderr, "book file open error!");
				exit(1);
			}
			for (int i = 0; i < 10; i++)
			{
				fscanf(bookfp, "%d %s", &books[i].id, &books[i].title);
				if (feof(bookfp))
				{
					break;
				}

			}
			fclose(bookfp);

			bookfp = fopen("book.txt", "w");
			if (bookfp == NULL)
			{
				fprintf(stderr, "book file open error!");
				exit(1);
			}
			cout << "write the id of a book to modify";
			cin >> book_modify_id;

			cout << "modify menu 1. modify id 2.modify title 3.both" << endl;
			cin >> book_modify_menu;
			if (book_modify_menu == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					if (book_modify_id == books[i].id)
					{
						cout << "write modified id" << endl;
						cin >> book_modify_id;
						books[i].id = book_modify_id;
						break;
					}
				}
			}
			else if (book_modify_menu == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					if (book_modify_id == books[i].id)
					{
						cout << "write modified title" << endl;
						cin >> book_modify_title;
						strcpy(books[i].title, book_modify_title);
						break;
					}
				}
			}
			else if (book_modify_menu == 3)
			{
				for (int i = 0; i < 10; i++)
				{
					if (book_modify_id == books[i].id)
					{
						cout << "write modified id and title" << endl;
						cin >> book_modify_id >> book_modify_title;
						books[i].id = book_modify_id;
						strcpy(books[i].title, book_modify_title);
						break;
					}
				}
			}
			else
			{
				cout << "choose between those 3 things." << endl;
			}

			for (int i = 0; i < 10; i++)
			{
				fprintf(bookfp, "%d %s \n", &books[i].id, &books[i].title);
				if (feof(bookfp))
				{
					break;
				}


			}

			fclose(bookfp);


			break;
		case 4: // book remove
			cout << "you chose to remove books" << endl;
			bookfp = fopen("book.txt", "w"); //w모드로 열면 전부 내용이 삭제됨.
			if (bookfp == NULL)
			{
				fprintf(stderr, "book file open error!");
				exit(1);
			}

			fclose(bookfp);
			break;
		case 5: // add a book
			bookfp = fopen("book.txt", "a");

			if (bookfp == NULL)
			{
				fprintf(stderr, "book file open error!");
				exit(1);
			}

			cout << "write id and title of a book which you want to add" << endl;
			cin >> book_append_id >> book_append_title;
			fprintf(bookfp, "%d %s\n", book_append_id, book_append_title);

			fclose(bookfp);

			break;

		case 6://member show
			memberfp = fopen("member.txt", "r");
			if (memberfp == NULL)
			{
				fprintf(stderr, "member file open error!");
				exit(1);
			}

			for (int i = 0; i < 5; i++)
			{
				fscanf(memberfp, "%d %s", &members[i].id, &members[i].name);
				if (feof(memberfp))
				{
					break;
				}
				cout << members[i].id << " " << members[i].name << endl;
			}

			fclose(memberfp);
			break;

		case 7: // member modify
			memberfp = fopen("member.txt", "r");

			if (memberfp == NULL)
			{
				fprintf(stderr, "member file open error!");
				exit(1);
			}
			for (int i = 0; i < 10; i++)
			{
				fscanf(memberfp, "%d %s", &members[i].id, &members[i].name);
				if (feof(memberfp))
				{
					break;
				}

			}
			fclose(memberfp);

			memberfp = fopen("member.txt", "w");
			if (memberfp == NULL)
			{
				fprintf(stderr, "member file open error!");
				exit(1);
			}
			cout << "write the id of a member to modify";
			cin >> member_modify_id;

			cout << "modify menu 1. modify id 2.modify name 3.both" << endl;
			cin >> member_modify_menu;
			if (member_modify_menu == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					if (member_modify_id == members[i].id)
					{
						cout << "write modified id" << endl;
						cin >> member_modify_id;
						members[i].id = member_modify_id;
						break;
					}
				}
			}
			else if (member_modify_menu == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					if (member_modify_id == members[i].id)
					{
						cout << "write modified name" << endl;
						cin >> member_modify_name;
						strcpy(members[i].name, member_modify_name);
						break;
					}
				}
			}
			else if (member_modify_menu == 3)
			{
				for (int i = 0; i < 10; i++)
				{
					if (member_modify_id == members[i].id)
					{
						cout << "write modified id and name" << endl;
						cin >> book_modify_id >> member_modify_name;
						members[i].id = member_modify_id;
						strcpy(members[i].name, member_modify_name);
						break;
					}
				}
			}
			else
			{
				cout << "choose between those 3 things." << endl;
			}

			for (int i = 0; i < 10; i++)
			{
				fprintf(memberfp, "%d %s \n", &members[i].id, &members[i].name);
				if (feof(memberfp))
				{
					break;
				}


			}

			fclose(memberfp);


			break;
		case 8: // member remove
			cout << "you chose to remove members" << endl;
			memberfp = fopen("member.txt", "w");
			if (memberfp == NULL)
			{
				fprintf(stderr, "member file open error!");
				exit(1);
			}

			fclose(memberfp);
			break;

		case 9: // add a member
			memberfp = fopen("member.txt", "a");

			if (memberfp == NULL)
			{
				fprintf(stderr, "member file open error!");
				exit(1);
			}

			cout << "write id and name of a member who you want to add" << endl;
			cin >> member_append_id >> member_append_name;
			fprintf(memberfp, "%d %s", member_append_id, member_append_name);

			fclose(memberfp);
			break;

		case 10: //borrow
			break;
		case 11: //return
			break;
		default:
			cout << "choose between 1 and 11" << endl;

		}
	}


	return 0;
}