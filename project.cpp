int main()
{
	struct book books[10]; // 책 10개
	struct member members[5]; // 책 5개

	FILE* bookfp;
	FILE* memberfp;
	FILE* managefp;

	int menu;

	int book_id;
	char book_title[30];

	while (1)
	{
		

		bookfp = fopen("book.txt", "r"); //읽기모드로 열기
		
		if (bookfp == NULL) // 오류상황시 처리
		{
			fprintf(stderr, "book file open error!");
			exit(1);
		}
		
		for (int i = 0; i < 10; i++) // 한 줄씩 가져오기
		{
			fscanf(bookfp, "%d %s", &books[i].id, books[i].title);
			if (feof(bookfp)) //파일포인터 밑에 배치해서 끝나면 break
			{
				break;
			}
			
		}
		

		
		

		fclose(bookfp); // 파일 닫기
		
		cout << "menu: 1.quit 2.book show 3.book modify 4.book remove 5.add a book 6.member show" << endl;
		cout << "7.member modify 8.member remove 9.add a member 10.borrow 11.return" << endl;
		cout << "menu: ";
		cin >> menu;
		switch (menu)
		{
		case 1: // quit
			cout << "you chose to quit";
			exit(1); // 모든 프로세스 종료
			break;
		case 2: //book show
			for (int i = 0; i < 10; i++)
			{
				cout << "id: " << books[i].id << " title: " << books[i].title << endl;
				
			}
			break;
		case 3: //book modify
			break;
		case 4: //book remove
			break;
		case 5: // add a book
			cout << "write the id and title of a book to add" << endl;
			cin >> book_id >> book_title;
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		default:
			cout << "choose between 1 and 11" << endl;

		}

	}

	return 0;
}