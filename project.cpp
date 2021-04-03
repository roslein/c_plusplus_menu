#include<iostream>
#define BOOK_NUM 10
#define MEMBER_NUM 5


using namespace std;

struct book
{
	int id; // 책 아이디
	char title[30]; // 책 제목
	int state; // 책 도서관에 빌린 상태면 0 책 반납되면 1
	int member; // 해당 책 빌린 사람 id 기록됨
};
struct member
{
	int id; //학생 아이디
	char name[30]; // 학생이름
	int state; // 해당구성원에게 책 없을 때는 0,책 빌리면 +1

};

int main()
{
	struct book books[BOOK_NUM]; // 책 10개
	struct member members[MEMBER_NUM]; // 구성원 5명


	FILE* bookfp;
	FILE* memberfp;
	FILE* managefp;

	int menu;


	int book_id;
	char book_title[30];
	int book_state;

	int member_id;
	char member_name[30];
	int member_state;

	int flag; // 이중루프 탈출변수

	while (1) // quit하기 전까지 나가지 않도록 처리
	{

		bookfp = fopen("book.txt", "r"); //읽기모드로 열기 > 읽어오기

		if (bookfp == NULL) // 오류상황시 처리
		{
			fprintf(stderr, "book file open error!");
			exit(1);
		}
		for (int i = 0; i < BOOK_NUM; i++) // books 초기화 >> 안쓰는 값이 출력되는 것 방지
		{
			books[i].id = NULL;
			strcpy(books[i].title, "NULL");
			books[i].state = 0;
			books[i].member = NULL;

		}

		for (int i = 0; i < BOOK_NUM; i++) // 한 줄씩 가져오기
		{
			fscanf(bookfp, "%d %s %d %d", &books[i].id, books[i].title, &books[i].state,&books[i].member);
			if (feof(bookfp)) //파일포인터 밑에 배치해서 끝나면 break
			{
				break;
			}

		}
		fclose(bookfp); // bookfp닫기

		memberfp = fopen("member.txt", "r"); // 읽기모드로 열기 > 읽어오기

		if (memberfp == NULL) // 오류 상황시 처리
		{
			fprintf(stderr, "member file open error!");
			exit(1);
		}
		for (int i = 0; i < MEMBER_NUM; i++) // members초기화 >> 안쓰는 값이 출력되는 것 방지
		{
			members[i].id = NULL;
			strcpy(members[i].name, "NULL");
			members[i].state = 0;

		}

		for (int i = 0; i < MEMBER_NUM; i++) // 한 줄씩 가져오기
		{
			fscanf(memberfp, "%d %s %d", &members[i].id, members[i].name, &members[i].state);
			if (feof(memberfp)) //파일포인터 밑에 배치해서 끝나면 break
			{
				break;
			}

		}
		fclose(memberfp); // 닫기


		//메뉴
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
			for (int i = 0; i < BOOK_NUM; i++)
			{
				if (books[i].id != NULL) // 빈자리만 빼고 출력
				{
					cout << "id: " << books[i].id << " title: " << books[i].title << " state: " << books[i].state  << " memeber_id who borrow this book: "<< books[i].member<< endl;
				}

			}
			break;
		case 3: // book modify > id를 입력받고 정보(책 제목) 수정
			cout << "write the id of a book to modify" << endl;
			cin >> book_id;

			for (int i = 0; i < BOOK_NUM; i++)
			{
				if (books[i].id == book_id)
				{
					cout << "write title to modify" << endl;
					cin >> book_title;
					strcpy(books[i].title, book_title);
					
					break;
				}
				else if ((i == BOOK_NUM - 1) && (books[i].id != book_id))
				{//그런 책이 없음 
					cout << "there is no such book." << endl;
					break;
				}
			}
			break;
		case 4: // book remove
			cout << "write the id of a book to remove" << endl;
			cin >> book_id;
			for (int i = 0; i < BOOK_NUM; i++)
			{
				if ((books[i].id == book_id) && (books[i].state == 1))
				{ // 책을 찾았고 그 책이 도서관에 있을 때 > 삭제 가능 >초기화
					cout << "book remove success" << endl;
					books[i].id = NULL;
					strcpy(books[i].title, "NULL");
					books[i].state = 0;
					books[i].member = NULL;
					break;
				}
				else if ((books[i].id == book_id) && (books[i].state == 0))
				{ // 책을 찾았는데 누가 빌려간 상태일 때 > 반납된 후 삭제해야
					cout << "someone has borrowed the book. try after return" << endl;
					break;
				}
				else if ((i == BOOK_NUM -1) && (books[i].id != book_id))
				{//그런 책이 없음 > 책이 없으므로 삭제 자체가 불가능
					cout << "there is no such book." << endl;
					break;
				}
			}
			break;
		case 5: // add a book

			cout << "write the id and title of a book to add" << endl;
			cin >> book_id >> book_title;

			flag = 0;
			for (int i = 0; i < BOOK_NUM; i++)
			{
				if (books[i].id == book_id)
				{ // 이미 있는 id 인 경우 등록 불가
					cout << "this id has already been registered!." << endl;
					flag = 1;
					break;
				}
			}
			if (flag == 1)
			{
				break;
			}

			for (int i = 0; i < BOOK_NUM; i++)
			{
				
				if (books[i].id == NULL)
				{ // 빈자리 찾았을 경우 > 빈자리에 입력
					cout << "adding a book success!" << endl;
					books[i].id = book_id;
					strcpy(books[i].title, book_title);
					books[i].state = 1; 
					// 빌린 사람 id는 이미 NULL이니까 수정할 필요가 없음
					break;
				}
				else if ((i == BOOK_NUM -1) && (members[i].id != NULL))
				{ //새책이고 마지막까지 찾았는데 빈자리가 없음 > 책 삭제하고 추가해라
					cout << "no room to add. remove a book." << endl;
					break;
				}

			}

			break;
		case 6: // member show
			for (int i = 0; i < MEMBER_NUM; i++)
			{
				if (members[i].id != NULL) // id가 NULL인 것만 빼고 실행하기
				{
					cout << "id: " << members[i].id << " name: " << members[i].name << " state: " << members[i].state << endl;
				}

			}
			break;
		case 7: // member modify >id 입력받고 해당 구성원 정보(이름) 수정
			cout << "write the id of a member to modify" << endl;
			cin >> member_id;

			for (int i = 0; i < MEMBER_NUM; i++)
			{
				if (members[i].id == member_id) // ID로 매칭해서 찾기
				{
					cout << "write name to modify" << endl;
					cin >> member_name;
					strcpy(members[i].name, member_name);
					break;
				}
				else if ((i == MEMBER_NUM - 1) && (members[i].id != member_id))
				{ // 그런 사람이 없음 >삭제 불가능
					cout << "there is no such member" << endl;
					break;
				}
			}
			break;
		case 8: // member remove
			cout << "write the id of a member to remove" << endl;
			cin >> member_id;
			for (int i = 0; i < MEMBER_NUM; i++)
			{
				if ((members[i].id == member_id) && (members[i].state == 0)) //ID로 매칭해서 찾기
				{ // 사람을 찾았고 빌린 책이 없음 > 삭제 가능
					cout << "member remove success" << endl;
					members[i].id = NULL; // NULL로 초기화해서 SHOW할때 못 보게하기
					strcpy(members[i].name, "NULL");
					//state는 이미 0이니까 수정할 필요가 없음
					break;
				}
				else if ((members[i].id == member_id) && (members[i].state > 0))
				{ // 사람을 찾았고 빌린 책이 있음 > 삭제 불가능
					cout << "this person borrowed a book. try after return." << endl;
					break;
				}
				else if ((i == MEMBER_NUM -1) && (members[i].id != member_id))
				{ // 그런 사람이 없음 >삭제 불가능
					cout << "there is no such member" << endl;
					break;
				}

			}
			break;
		case 9: // add a member

			cout << "write the id and name of a member to add" << endl;
			cin >> member_id >> member_name;

			flag = 0;
			for (int i = 0; i < MEMBER_NUM; i++)
			{
				if (members[i].id == member_id)
				{ // 이미 있는 id 인 경우 등록 불가
					cout << "this id has already been registered!." << endl;
					flag = 1;
					break;
				}
			}
			if (flag == 1)
			{
				break;
			}

			for (int i = 0; i < MEMBER_NUM; i++)
			{
				if (members[i].id == NULL) //빈자리 찾기(ID가 NULL)
				{
					cout << "adding a member success! " << endl;
					members[i].id = member_id;
					strcpy(members[i].name, member_name);
					//state는 이미 0 이니까 수정할 필요 없음
					break;
				}
				else if ((i == MEMBER_NUM -1) && members[i].id != NULL)
				{//마지막까지 찾았는데 빈자리가 없는 경우
					cout << "no room to add. remove a member" << endl;
					break;
				}

			}

			break;
		case 10: // borrow
			cout << "write the id of a book to borrow and id of a member to borrow that book" << endl;
			cin >> book_id >> member_id; // 빌린 책과 빌린 사람 입력


			flag = 0;
			for (int j = 0; j < MEMBER_NUM; j++)
			{
				if (members[j].id == member_id)
				{ // 구성원 내에 있음 > 이제 책이 있는지 체크
					for (int i = 0; i < BOOK_NUM; i++)
					{
						if ((books[i].id == book_id) && (books[i].state == 1))
						{ // 책을 찾고 그 책이 도서관에 있으면 빌린다!
							cout << "borrow success!" << endl;
							books[i].state = 0; // 책 재고는 0
							books[i].member = member_id; // 빌린 사람 id 기록
							members[j].state += 1; // 멤버가 빌린 책 개수는 +1

							managefp = fopen("manage.txt", "a"); //manage 파일에 내역 업로드
							if (managefp == NULL)
							{
								fprintf(stderr, "manage file open error!");
								exit(1);
							}
							fprintf(managefp, "borrowed book:%d by %d \n", book_id, member_id);
							fclose(managefp);

							flag = 1;
							break;//이제 이중 for문 빠져나가고 프로그램 종료
						}
						else if ((books[i].id == book_id) && (books[i].state == 0))
						{ // 책을 찾았는데 책 재고가 없는 경우
							cout << "It has been out of stock." << endl;
							flag = 1;
							break;
						}
						else if ((i == BOOK_NUM -1) && (books[i].id != book_id))
						{//그런 책이 없음 >> 그대로 종료
							cout << "there is no such book. " << endl;
							flag = 1;
							break;
						}
					}

				}
				else if ((j == MEMBER_NUM -1) && (members[j].id != member_id))
				{ // 그런 구성원이 없음 > 그대로 종료
					cout << "there is no such member." << endl;
					break;
				}
				if (flag == 1) // 이중루프 탈출
				{
					break;
				}
			}



			
			break; // case 10 종료

		case 11: // return 
			cout << "write the id of a book to return and id of a member to return that book" << endl;
			cin >> book_id >> member_id;

			flag = 0;
			for (int j = 0; j < MEMBER_NUM; j++)
			{
				if ((members[j].id == member_id) && (members[j].state > 0))
				{ // 구성원 내에 있고 구성원이 빌린책이 있음 > 이제 그런 책이 있는지 체크
					for (int i = 0; i < BOOK_NUM; i++)
					{
						if ((books[i].id == book_id)&& (books[i].member == member_id))
						{ // 책 확인,빌린 사람 일치 확인 > 반납가능
							cout << "return sucess! " << endl;
							books[i].state = 1; // 도서관에 있는 상태로
							books[i].member = NULL; // 빌린 사람 이름 초기화
							members[j].state -= 1; // 빌린 책 개수는 -1

							managefp = fopen("manage.txt", "a"); //manage 파일에 내역 업로드
							if (managefp == NULL)
							{
								fprintf(stderr, "manage file open error!");
								exit(1);
							}
							fprintf(managefp, "returned book:%d by %d \n", book_id, member_id);
							fclose(managefp);

							flag = 1; //이중루프 빠져나오기
							break;
						}
						else if ((books[i].id == book_id) && (books[i].member != member_id))
						{ // 책은 확인했는데 빌린 사람이 이 사람이 아님.
							cout << "this book is not a book that you borrowed." << endl;
							flag = 1;
							break;
						}
						else if ((i == BOOK_NUM -1) && (books[i].id != book_id))
						{//그런 책은 존재하지 않음 > 반납이 불가능
							cout << "there is no such book." << endl;
							flag = 1; // 이중루프 빠져나오기
							break;
						}
					}

				}
				else if ((members[j].id == member_id) && (members[j].state == 0))
				{ // 구성원 내에 있지만 빌린 책이 없음
					cout << "this member borrowed nothing" <<endl;
					break;
				}
				else if ((j == MEMBER_NUM -1) && (members[j].id != member_id))
				{ // 그런 구성원이 없음 > 그대로 종료
					cout << "there is no such member." << endl;
					break;
				}
				if (flag == 1) // 이중루프 탈출
				{
					break;
				}
			}

			
			break; // case 11 종료




		default:
			cout << "choose between 1 and 11" << endl;
		}
		//메뉴 한번 실행마다 파일에 업로드
		bookfp = fopen("book.txt", "w"); //book.txt파일에 업데이트
		if (bookfp == NULL) // 오류상황시 처리
		{
			fprintf(stderr, "book file open error!");
			exit(1);
		}
		for (int i = 0; i < BOOK_NUM; i++)
		{
			fprintf(bookfp, "%d %s %d %d \n", books[i].id, books[i].title, books[i].state,books[i].member);
		}

		fclose(bookfp);

		memberfp = fopen("member.txt", "w"); // member.txt파일에 업로드
		if (memberfp == NULL) // 오류상황시 처리
		{
			fprintf(stderr, "member file open error!");
			exit(1);
		}
		for (int i = 0; i < MEMBER_NUM; i++)
		{
			fprintf(memberfp, "%d %s %d \n", members[i].id, members[i].name, members[i].state);
		}

		fclose(memberfp);


	}

	return 0;
}