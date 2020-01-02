#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

typedef struct character
{	
	// 이름, 공격력, 현재생명력, 현재경험치, 주는 경험치, 레벨, 최대경험치, 최대 생명력, 플레이어구분(참=1)
	char name[50];
	int att;
	int currentHp;
	int currentExp;
	int getExp;
	int level;
	int maxExp;
	int maxHp;
	int isPlayer;
}Character;

void ShowCharacter(Character* character)
{
	printf("======%s(%dLv)======\n", character->name, character->level);
	printf("공격력 = %d\t", character->att);
	printf("생명력 = %d/%d\n", character->currentHp, character->maxHp);
	printf("경험치 = %d/%d\t", character->currentExp, character->maxExp);
	printf("GetExp : %d\n", character->getExp);
}

void IntoDunGeon(Character* player, Character* monster)
{
	int select = 0;
	while (1)
	{
		srand((unsigned)time(NULL));
		int monsterSelect = rand() % 3;

		system("cls");
		ShowCharacter(player);
		ShowCharacter(monster);
		printf("%s 입력\n", player->name);
		printf("가위 : 0, 바위 : 1, 보 : 2\n");
		printf("입력 : ");
		scanf("%d", &select);

		switch (select)
		{
		case 0:
			printf("%s : 가위!!\n", player->name);
			break;
		case 1:
			printf("%s : 바위!!\n", player->name);
			break;
		case 2:
			printf("%s : 보!!\n", player->name);
			break;
		default:
			while (select < 0 || select>2)
			{
				printf("잘못입력 다시\n");
				printf("가위 : 0, 바위 : 1, 보 : 2\n");
				printf("입력 : ");
				scanf("%d", &select);
			}
			break;
		}

		switch (monsterSelect)
		{
		case 0:
			printf("%s : 가위!!\n", monster->name);
			break;
		case 1:
			printf("%s : 바위!!\n", monster->name);
			break;
		case 2:
			printf("%s : 보!!\n", monster->name);
			break;
		}

		if (select == monsterSelect)
		{
			printf("무승부...\n");
		}
		else if ((select == 0 && monsterSelect == 1) || (select == 1 && monsterSelect == 2) || (select == 2 && monsterSelect == 0))
		{
			// 플레이어가 패배
			player->currentHp -= monster->att;
		}
		else
		{
			// 몬스터가 패배
			monster->currentHp -= player->att;
		}
		system("pause");

		// 플레이어가 죽은 경우
		if (player->currentHp <= 0)
		{
			system("cls");
			printf("%s가 승리!!\n", monster->name);
			printf("%s가 경험치 %d를 얻었습니다.\n", monster->name, player->getExp);
			monster->currentExp += player->getExp;
			if (monster->currentExp >= monster->maxExp)
			{
				// 공격력 0~4 증가
				// 생명력 0~10 증가
				// 방어력은 1 고정 증가
				srand((unsigned)time(NULL));
				int randomAttUp = rand() % 4;
				int randomHPUp = rand() % 10;

				if (monster->level == 1)
				{
					monster->maxExp++;
				}
				printf("%s 레벨업!!\n", monster->name);
				monster->level++;
				monster->currentExp -= monster->maxExp;
				monster->maxExp += monster->level;
				printf("공격력 %d 증가!!\n", randomAttUp);
				monster->att += randomAttUp;
				printf("생명력 %d 증가!!\n", randomHPUp);
				monster->maxHp += randomHPUp;
				monster->currentHp = monster->maxHp;
				if (monster->level == 1)
				{
					monster->maxExp++;
				}
			}
			if (player->currentExp == 0)
			{
				printf("Game Over\n");
				system("pause");
				return;
			}
			system("pause");
			break;
		}

		// 몬스터가 죽은 경우
		if (monster->currentHp <= 0)
		{
			system("cls");
			printf("%s가 승리!!\n", player->name);
			printf("%s가 경험치 %d를 얻었습니다.\n", player->name, monster->getExp);
			player->currentExp += monster->getExp;
			player->getExp += monster->getExp;
			if (player->currentExp >= player->maxExp)
			{
				// 공격력 0~4 증가
				// 생명력 0~10 증가
				// 방어력은 1 고정 증가
				srand((unsigned)time(NULL));
				int randomAttUp = rand() % 5;
				int randomHPUp = rand() % 11;

				printf("%s 레벨업!!\n", player->name);
				player->level++;
				player->currentExp -= player->maxExp;
				player->getExp = 0;
				player->maxExp += player->level;
				printf("공격력 %d 증가!!\n", randomAttUp);
				player->att += randomAttUp;
				printf("생명력 %d 증가!!\n", randomHPUp);
				player->maxHp += randomHPUp;
				player->currentHp = player->maxHp;
				if (player->level == 1)
				{
					player->maxExp++;
				}
			}
			monster->currentHp = monster->maxHp;
			system("pause");
			break;
		}
	}
}

void SetCount(int* characterCount)
{
	int tempCount;
	FILE* f;
	f = fopen("Default.txt", "r");
	if (f == NULL)
	{
		printf("플레이정보가 없습니다.");
		system("pause");
		return;
	}
	else
	{
		fscanf(f, "%*d %*d %*d %*d %*d %*d %d", &tempCount);
	}
	*characterCount = tempCount + 1;
}

void ShowSaveSlot()
{
	char fileName[20];

	FILE* f;
	for (int i = 1; i <= 10; i++)
	{
		sprintf(fileName, "SaveFile%d.txt", i);
		f = fopen(fileName, "r");
		if (f == NULL)
		{
			printf("%d번슬롯 : (파일여부 : X)\n", i);
		}
		else
		{
			printf("%d번슬롯 : (파일여부 : 0)\n", i);
			fclose(f);
		}
	}
}

void Save(int select, Character* character, int characterCount)
{
	char fileName[20];
	sprintf(fileName, "SaveFile%d.txt", select);
	FILE *f;
	if (select <= 0 || select > 10)
	{
		printf("잘못선택하였습니다.\n");
		system("pause");
	}
	else
	{
		// 저장 문서 정보
		// 이름, 공격력, 현재생명력, 현재경험치, 주는 경험치, 레벨, 최대경험치, 최대 생명력, 플레이어구분(참=1)
		f = fopen(fileName, "w");
		fprintf(f, "%s %d %d %d %d %d %d %d %d\n",
			character[0].name, character[0].att, character[0].currentHp, character[0].currentExp, character[0].getExp, character[0].level,
			character[0].maxExp, character[0].maxHp, character[0].isPlayer);
		fprintf(f, "%d\n", characterCount - 1);
		for (int i = 1; i < characterCount; i++)
		{
			fprintf(f, "%s %d %d %d %d %d %d %d %d\n",
				character[i].name, character[i].att, character[i].currentHp, character[i].currentExp, character[i].getExp, character[i].level,
				character[i].maxExp, character[i].maxHp, character[i].isPlayer);
		}
		fclose(f);
		printf("저장 완료!!\n");
	}
}

void Load(int select, Character* character, int* characterCount)
{
	char fileName[20];
	sprintf(fileName, "SaveFile%d.txt", select);
	FILE *f;
	if (select <= 0 || select > 10)
	{
		printf("잘못선택하였습니다.\n");
		system("pause");
	}
	else
	{
		if (character != NULL)
		{
			free(character);
		}

		int tempCount;
		FILE* f;
		f = fopen(fileName, "r");
		if (f == NULL)
		{
			printf("플레이정보가 없습니다.");
			system("pause");
			return;
		}
		else
		{
			fscanf(f, "%*s %*d %*d %*d %*d %*d %*d %*d %*d %d", &tempCount);
		}
		*characterCount = tempCount + 1;

		Character* tempcharacter;
		tempcharacter = &(*character);
		tempcharacter = (Character*)malloc(sizeof(Character)*(*characterCount));

		f = fopen(fileName, "r");
		// 이름, 공격력, 공격속도, 현재생명력, 방어력, 방어(1=On, 0=Off), 현재경험치, 주는 경험치, 레벨, 최대경험치, 최대 생명력, 플레이어구분(참=1)
		fscanf(f, "%s %d %d %d %d %d %d %d %d",
			tempcharacter[0].name, &tempcharacter[0].att, &tempcharacter[0].currentHp,
			&tempcharacter[0].currentExp, &tempcharacter[0].getExp, &tempcharacter[0].level,
			&tempcharacter[0].maxExp, &tempcharacter[0].maxHp, &tempcharacter[0].isPlayer);
		fscanf(f, "%*d\n");


		for (int i = 1; i <= tempCount; i++)
		{
			fscanf(f, "%s %d %d %d %d %d %d %d %d",
				tempcharacter[i].name, &tempcharacter[i].att, &tempcharacter[i].currentHp,
				&tempcharacter[i].currentExp, &tempcharacter[i].getExp, &tempcharacter[i].level,
				&tempcharacter[i].maxExp, &tempcharacter[i].maxHp, &tempcharacter[i].isPlayer);
		}
		fclose(f);
	}
}

int main()
{
	char tempName[50];
	int select, characterCount;
	Character* character_List = NULL;
	FILE* f;

	SetCount(&characterCount);
	character_List = (Character*)malloc(sizeof(Character)*characterCount);
	
	printf("플레이어 이름 입력 : ");
	scanf("%s", tempName);

	f = fopen("Default.txt", "r");
	if (f == NULL)
	{
		printf("플레이정보가 없습니다.");
		system("pause");
		return 0;
	}
	else
	{
		// 플레이어 Default 가져옴
		strcpy(character_List[0].name, tempName);
		fscanf(f, "%d", &character_List[0].att);
		fscanf(f, "%d", &character_List[0].maxHp);
		character_List[0].currentHp = character_List[0].maxHp;
		fscanf(f, "%d", &character_List[0].maxExp);
		character_List[0].currentExp = 0;
		fscanf(f, "%d", &character_List[0].getExp);
		character_List[0].level = 1;
		fscanf(f, "%d", &character_List[0].level);
		fscanf(f, "%d %*d", &character_List[0].isPlayer);

		// 몬스터 Default 가져옴
		for (int i = 1; i <= characterCount; i++)
		{
			fscanf(f, "%s", character_List[i].name);
			fscanf(f, "%d", &character_List[i].att);
			fscanf(f, "%d", &character_List[i].maxHp);
			character_List[i].currentHp = character_List[i].maxHp;
			fscanf(f, "%d", &character_List[i].maxExp);
			character_List[i].currentExp = 0;
			fscanf(f, "%d", &character_List[i].getExp);
			fscanf(f, "%d", &character_List[i].level);
			fscanf(f, "%d", &character_List[i].isPlayer);
		}
	}
	fclose(f);

	while (1)
	{
		system("cls");
		printf("======DunGeon======\n");
		printf("    1.던전 입장\n");
		printf("    2.Play 정보\n");
		printf("    3.Save\n");
		printf("    4.Load\n");
		printf("    5.종료\n");
		printf("    입력 : ");
		scanf("%d", &select);

		switch (select)
		{
		case 1:
			while (1)
			{
				system("cls");
				printf("=====던전 입구=====\n");
				for (int i = 1; i < characterCount; i++)
				{
					printf("     %d.%d층던전 : [%s]\n", i, i, character_List[i].name);
				}
				printf("     %d.돌아가기\n", characterCount);
				printf("선택 : ");
				select = 0;
				scanf("%d", &select);
				if (select != characterCount)
				{
					IntoDunGeon(&character_List[0], &character_List[select]);
				}
				if (select == characterCount)
				{
					break;
				}
			}
			break;
		case 2:
			system("cls");
			ShowCharacter(&character_List[0]);
			printf("\n\n\n");
			printf("=====Enemy=====\n");
			for (int i = 1; i < characterCount; i++)
			{
				ShowCharacter(&character_List[i]);
			}
			system("pause");
			break;
		case 3:
			system("cls");
			printf("=====Save=====\n");
			ShowSaveSlot();
			printf("선택 : ");
			select = 0;
			scanf("%d", &select);
			Save(select, character_List, characterCount);
			break;
		case 4:
			system("cls");
			printf("=====Load=====\n");
			ShowSaveSlot();
			printf("선택 : ");
			select = 0;
			scanf("%d", &select);
			Load(select, character_List, &characterCount);
			break;
		case 5:
			if (character_List != NULL)
			{
				free(character_List);
			}
			return 0;
		default:
			break;
		}
	}


	return 0;
}