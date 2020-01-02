#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

typedef struct character
{	
	// �̸�, ���ݷ�, ��������, �������ġ, �ִ� ����ġ, ����, �ִ����ġ, �ִ� �����, �÷��̾��(��=1)
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
	printf("���ݷ� = %d\t", character->att);
	printf("����� = %d/%d\n", character->currentHp, character->maxHp);
	printf("����ġ = %d/%d\t", character->currentExp, character->maxExp);
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
		printf("%s �Է�\n", player->name);
		printf("���� : 0, ���� : 1, �� : 2\n");
		printf("�Է� : ");
		scanf("%d", &select);

		switch (select)
		{
		case 0:
			printf("%s : ����!!\n", player->name);
			break;
		case 1:
			printf("%s : ����!!\n", player->name);
			break;
		case 2:
			printf("%s : ��!!\n", player->name);
			break;
		default:
			while (select < 0 || select>2)
			{
				printf("�߸��Է� �ٽ�\n");
				printf("���� : 0, ���� : 1, �� : 2\n");
				printf("�Է� : ");
				scanf("%d", &select);
			}
			break;
		}

		switch (monsterSelect)
		{
		case 0:
			printf("%s : ����!!\n", monster->name);
			break;
		case 1:
			printf("%s : ����!!\n", monster->name);
			break;
		case 2:
			printf("%s : ��!!\n", monster->name);
			break;
		}

		if (select == monsterSelect)
		{
			printf("���º�...\n");
		}
		else if ((select == 0 && monsterSelect == 1) || (select == 1 && monsterSelect == 2) || (select == 2 && monsterSelect == 0))
		{
			// �÷��̾ �й�
			player->currentHp -= monster->att;
		}
		else
		{
			// ���Ͱ� �й�
			monster->currentHp -= player->att;
		}
		system("pause");

		// �÷��̾ ���� ���
		if (player->currentHp <= 0)
		{
			system("cls");
			printf("%s�� �¸�!!\n", monster->name);
			printf("%s�� ����ġ %d�� ������ϴ�.\n", monster->name, player->getExp);
			monster->currentExp += player->getExp;
			if (monster->currentExp >= monster->maxExp)
			{
				// ���ݷ� 0~4 ����
				// ����� 0~10 ����
				// ������ 1 ���� ����
				srand((unsigned)time(NULL));
				int randomAttUp = rand() % 4;
				int randomHPUp = rand() % 10;

				if (monster->level == 1)
				{
					monster->maxExp++;
				}
				printf("%s ������!!\n", monster->name);
				monster->level++;
				monster->currentExp -= monster->maxExp;
				monster->maxExp += monster->level;
				printf("���ݷ� %d ����!!\n", randomAttUp);
				monster->att += randomAttUp;
				printf("����� %d ����!!\n", randomHPUp);
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

		// ���Ͱ� ���� ���
		if (monster->currentHp <= 0)
		{
			system("cls");
			printf("%s�� �¸�!!\n", player->name);
			printf("%s�� ����ġ %d�� ������ϴ�.\n", player->name, monster->getExp);
			player->currentExp += monster->getExp;
			player->getExp += monster->getExp;
			if (player->currentExp >= player->maxExp)
			{
				// ���ݷ� 0~4 ����
				// ����� 0~10 ����
				// ������ 1 ���� ����
				srand((unsigned)time(NULL));
				int randomAttUp = rand() % 5;
				int randomHPUp = rand() % 11;

				printf("%s ������!!\n", player->name);
				player->level++;
				player->currentExp -= player->maxExp;
				player->getExp = 0;
				player->maxExp += player->level;
				printf("���ݷ� %d ����!!\n", randomAttUp);
				player->att += randomAttUp;
				printf("����� %d ����!!\n", randomHPUp);
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
		printf("�÷��������� �����ϴ�.");
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
			printf("%d������ : (���Ͽ��� : X)\n", i);
		}
		else
		{
			printf("%d������ : (���Ͽ��� : 0)\n", i);
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
		printf("�߸������Ͽ����ϴ�.\n");
		system("pause");
	}
	else
	{
		// ���� ���� ����
		// �̸�, ���ݷ�, ��������, �������ġ, �ִ� ����ġ, ����, �ִ����ġ, �ִ� �����, �÷��̾��(��=1)
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
		printf("���� �Ϸ�!!\n");
	}
}

void Load(int select, Character* character, int* characterCount)
{
	char fileName[20];
	sprintf(fileName, "SaveFile%d.txt", select);
	FILE *f;
	if (select <= 0 || select > 10)
	{
		printf("�߸������Ͽ����ϴ�.\n");
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
			printf("�÷��������� �����ϴ�.");
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
		// �̸�, ���ݷ�, ���ݼӵ�, ��������, ����, ���(1=On, 0=Off), �������ġ, �ִ� ����ġ, ����, �ִ����ġ, �ִ� �����, �÷��̾��(��=1)
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
	
	printf("�÷��̾� �̸� �Է� : ");
	scanf("%s", tempName);

	f = fopen("Default.txt", "r");
	if (f == NULL)
	{
		printf("�÷��������� �����ϴ�.");
		system("pause");
		return 0;
	}
	else
	{
		// �÷��̾� Default ������
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

		// ���� Default ������
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
		printf("    1.���� ����\n");
		printf("    2.Play ����\n");
		printf("    3.Save\n");
		printf("    4.Load\n");
		printf("    5.����\n");
		printf("    �Է� : ");
		scanf("%d", &select);

		switch (select)
		{
		case 1:
			while (1)
			{
				system("cls");
				printf("=====���� �Ա�=====\n");
				for (int i = 1; i < characterCount; i++)
				{
					printf("     %d.%d������ : [%s]\n", i, i, character_List[i].name);
				}
				printf("     %d.���ư���\n", characterCount);
				printf("���� : ");
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
			printf("���� : ");
			select = 0;
			scanf("%d", &select);
			Save(select, character_List, characterCount);
			break;
		case 4:
			system("cls");
			printf("=====Load=====\n");
			ShowSaveSlot();
			printf("���� : ");
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