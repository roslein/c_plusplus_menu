#include<iostream>
#define book_num 10
#define member_num 5
#define empty 0

using namespace std;

struct book
{
	int id ; // 책 아이디
	char title[30]; // 책 제목
	int state; // 책 도서관에 없으면 0 책 반납되거나 add되면 +1
};
struct member
{
	int id; //학생 아이디
	char name[30]; // 학생이름
	int state; // 해당구성원에게 책 없을 때는 0,책 빌리면 +1
	
};

int main()
{
	struct book books[book_num] = { 0 }; // 책 10종류 > 0으로 초기화해서 id가 0 인건 빈자리인 것으로 생각
	struct member members[member_num] = { 0 }; // 구성원 5명


	FILE* bookfp;
	FILE* memberfp;
	FILE* managefp;

	int menu;


	int book_id;
	char book_title[30];
	int book_state;

	int member_id;
	char member_name[30];

	int flag; // 이중루프 탈출변수

	while (1) // quit하기 전까지 나가지 않도록 처리
	{

		bookfp = fopen("book.txt", "r"); //읽기모드로 열기 > 읽어오기

		if (bookfp == NULL) // 오류상황시 처리
		{
			fprintf(stderr, "book file open error!");
			exit(1);
		}
		for (int i = 0; i < book_num; i++) // books 초기화 >> 안쓰는 값이 출력되는 것 방지
		{
			books[i].id = empty;
			strcpy(books[i].title, "0");
			books[i].state = 0;

		}

		for (int i = 0; i < book_num; i++) // 한 줄씩 가져오기
		{
			fscanf(bookfp, "%d %s %d", &books[i].id, books[i].title,&books[i].state);
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
		for (int i = 0; i < member_num; i++) // members초기화 >> 안쓰는 값이 출력되는 것 방지
		{
			members[i].id = empty;
			strcpy(members[i].name, "0");
			members[i].state = 0;

		}
		
		

		for (int i = 0; i < member_num; i++) // 한 줄씩 가져오기
		{
			fscanf(memberfp, "%d %s %d", &members[i].id, members[i].name,&members[i].state);
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
			for (int i = 0; i < book_num; i++)
			{
				if (books[i].id != empty) // 빈 목록(id가 0인거)제외하고 보여주기
				{
					cout << "id: " << books[i].id << " title: " << books[i].title << " state: " << books[i].state<< endl;
				}

			}
			break;
		case 3: // book modify > id를 입력받고 정보(책 제목과 개수) 수정
			cout << "write the id of a book to modify" << endl;
			cin >> book_id;
			
			for (int i = 0; i < book_num; i++)
			{
				if (books[i].id == book_id)
				{
					cout << "write modified title" << endl;
					cin >> book_title >> book_state;
					strcpy(books[i].title, book_title);
					books[i].state = book_state;
					break;
				}
			}
			break;
		case 4: // book remove
			cout << "write the id of a book to remove" << endl;
			cin >> book_id;
			for (int i = 0; i < book_num; i++)
			{
				if ( (books[i].id == book_id) && (books[i].state >0))
				{ // 책을 찾았고 그 책이 도서관에 있을 때 > 삭제 가능 >초기화
					books[i].id = empty;
					strcpy(books[i].title, "0");
					books[i].state = 0;
					break;
				}
				else if ((books[i].id == book_id) && (books[i].state == 0))
				{ // 책을 찾았는데 누가 빌려간 상태일 때 > 반납된 후 삭제해야
					cout << "someone has borrowed the book. try after return" << endl;
					break;
				}
				else if ((i == 9) && (books[i].id != book_id))
				{//그런 책이 없음 > 책이 없으므로 삭제 자체가 불가능
					cout << "there is no such book." << endl;
					break;
				}
			}
			break;
		case 5: // add a book
		
			cout << "write the id and title of a book to add" << endl;
			cin >> book_id >> book_title;
			
			for (int i = 0; i < book_num; i++)
			{
				if (books[i].id == book_id)
				{ // 이미 있던 책의 재고를 늘리려는 경우
					books[i].state += 1;

					break;
				}
				else if (books[i].id == empty)
				{ // 새책이고 빈자리 찾았을 경우 > 빈자리에 입력
					books[i].id = book_id;
					strcpy(books[i].title, book_title);
					books[i].state = 1; // 새책이니까 1개부터 시작
					break;
				}
				else if ((i == 9) && (members[i].id != empty))
				{ //새책이고 마지막까지 찾았는데 빈자리가 없음 > 책 삭제하고 추가해라
					cout << "no room to add. remove a book." << endl;
					break;
				}

			}
			
			break;
		case 6: // member show
			for (int i = 0; i < member_num; i++)
			{
				if (members[i].id != empty) // 빈자리 즉 id가 0인 것만 빼고 보여주기
				{
					cout << "id: " << members[i].id << " name: " << members[i].name << " state: " << members[i].state << endl;
				}

			}
			break;
		case 7: // member modify
			cout << "write the id of a member to modify" << endl;
			cin >> member_id;

			for (int i = 0; i < member_num; i++)
			{
				if (members[i].id == member_id) // ID로 매칭해서 찾기
				{
					cout << "write modified name" << endl;
					cin >> member_name;
					strcpy(members[i].name, member_name);
					break;
				}
			}
			break;
		case 8: // member remove
			cout << "write the id of a member to remove" << endl;
			cin >> member_id;
			for (int i = 0; i < member_num; i++)
			{
				if ( (members[i].id == member_id) && (members[i].state == 0)) //ID로 매칭해서 찾기
				{ // 사람을 찾았고 빌린 책이 없음 > 삭제 가능
					members[i].id = empty; // 초기화해서 SHOW할때 못 보게하기
					strcpy(members[i].name, "0"); 
					//state는 0이니까 초기화할 필요가 없음
					break;
				}
				else if ((members[i].id == member_id) && (members[i].state > 0))
				{ // 사람을 찾았고 빌린 책이 있음 > 삭제 불가능
					cout << "this person borrowed a book. try after return." << endl;
					break;
				}
				else if ((i == 4) && (members[i].id != member_id))
				{ // 그런 사람이 없음 >삭제 불가능
					cout << "there is no such member" << endl;
					break;
				}
				
			}
			break;
		case 9: // add a member
			
			cout << "write the id and name of a member to add" << endl;
			cin >> member_id >> member_name;

			for (int i = 0; i < member_num; i++)
			{
				if (members[i].id == empty) //빈자리 찾기
				{
					members[i].id = member_id;
					strcpy(members[i].name, member_name);
					break;
				}
				else if ((i == 4) && members[i].id != empty)
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
			for (int j = 0; j < member_num; j++)
			{
				if (members[j].id == member_id)
				{ // 구성원 내에 있음 > 이제 책이 있는지 체크
					for (int i = 0; i < book_num; i++)
					{ 
						if ((books[i].id == book_id) && (books[i].state > 0))
						{ // 책을 찾고 그 책이 도서관에 있으면 빌린다!
							cout << "borrowing success!" << endl;
							books[i].state -=1; // 책 재고에서 1개 빼내고
							members[j].state += 1; // 멤버가 빌린 책에는 +1
							flag = 1;
							break;//이제 이중 for문 빠져나가고 프로그램 종료
						}
						else if ((books[i].id == book_id) && (books[i].state == 0))
						{ // 책을 찾았는데 책 재고가 없는 경우
							cout << "It has been out of stock." << endl;
							flag = 1;
							break;
						}
						else if ((i == 9) && (books[i].id != book_id))
						{//그런 책이 없음 >> 그대로 종료
							cout << "there is no such book. " << endl;
							flag = 1;
							break;
						}
					}
					
				}
				else if ((j == 4) && (members[j].id != member_id))
				{ // 그런 구성원이 없음 > 그대로 종료
					cout << "there is no such member." << endl;
					break;
				}
				if (flag == 1) // 이중루프 탈출
				{
					break;
				}
			}
			
			
			
			managefp = fopen("manage.txt", "a"); //manage 파일에 내역 업로드
			if (managefp == NULL)
			{
				fprintf(stderr, "manage file open error!");
				exit(1);
			}
			fprintf(managefp, "borrowed book:%d by %d \n", book_id, member_id);
			fclose(managefp);
			break; // case 10 종료
		case 11: // return 
			cout << "write the id of a book to return and id of a member to return that book" << endl; 
			cin >> book_id >> member_id;
			
			flag = 0;
			for (int j = 0; j < member_num; j++)
			{
				if ( (members[j].id == member_id) && (members[j].state >0))
				{ // 구성원 내에 있고 구성원이 빌린책이 있음 > 이제 그런 책이 있는지 체크
					for (int i = 0; i < book_num; i++)
					{
						if (books[i].id == book_id)
						{ // 책 확인 
							cout << " return sucess! " << endl;
							books[i].state += 1; // 재고는  +1
							members[j].state -=1; // 빌린 책 개수는 -1
							flag = 1; //이중루프 빠져나오기
							break;
						}
						else if ((i == 9) && (books[i].id != book_id))
						{//그런 책은 존재하지 않음
							cout << "there is no such book. return after adding it" << endl;
							flag = 1;
							break;
						}
					}

				}
				else if ((members[j].id == member_id) && (members[j].state == 0))
				{ // 구성원 내에 있지만 빌린 책이 없음
					cout << "this member borrowed nothing";
					break;
				}
				else if ((j == 4) && (members[j].id != member_id))
				{ // 그런 구성원이 없음 > 그대로 종료
					cout << "there is no such member." << endl;
					break;
				}
				if (flag == 1) // 이중루프 탈출
				{
					break;
				}
			}
			
			managefp = fopen("manage.txt", "a"); //manage 파일에 내역 업로드
			if (managefp == NULL)
			{
				fprintf(stderr, "manage file open error!");
				exit(1);
			}
			fprintf(managefp, "returned book:%d by %d \n", book_id, member_id);
			fclose(managefp);
			break; // case 11 종료


			

		default:
			cout << "choose between 1 and 11" << endl;
		}
		
		bookfp = fopen("book.txt", "w"); //book.txt파일에 업데이트
		if (bookfp == NULL) // 오류상황시 처리
		{
			fprintf(stderr, "book file open error!");
			exit(1);
		}
		for (int i = 0; i < book_num; i++)
		{
			fprintf(bookfp, "%d %s %d \n", books[i].id, books[i].title,books[i].state);
		}

		fclose(bookfp);

		memberfp = fopen("member.txt", "w");
		if (memberfp == NULL) // 오류상황시 처리
		{
			fprintf(stderr, "member file open error!");
			exit(1);
		}
		for (int i = 0; i < member_num; i++)
		{
			fprintf(memberfp, "%d %s %d \n", members[i].id, members[i].name,members[i].state);
		}

		fclose(memberfp);


	}
	
	return 0;
}