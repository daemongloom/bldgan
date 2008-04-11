#ifndef _PLAYLIST_H_
  #define _PLAYLIST_H_

#define TCPL 5             // ���������� ��   AAA

// ��������� ��� ����� ��������� ��� � ������������� ����... � �� ����� ����������! :D  AAA
void DisableScroll(void);

// ��������� ���������
void VolumeUp();

// �������� ���������
void VolumeDown();

// ��������� �� ����
void ToggleVolume();

// ��������� ����
void RandTrack();

//������������� ����  AAA
void RepeatTrack();

// ��� plamode==1  AAA
void NextTrackX();

// ��������� ���� ��  AAA
void NextTrack();

// ���������� ���� ��  AAA
void PreviousTrack();

// �����/���������������
void TogglePlayback();

// ������������� ������������
void StopAllPlayback();

// ���������� � �������   AAA
void SetNextPlayed();

// ��������������� ������������� � �������   AAA
void PlaySetTrack();

// ��������� ��   AAA
void NextPL();

// ���������� ��   AAA
void PrevPL();

// ������������� ��� ����������� ����� AAA
void CTtoFirst();

// ������ � ��� ��� �������� AAA
void PTtoFirst();

//������� �������� ���� AAA
void CTDown();

//������� �������� ����� AAA
void CTUp();

// ������� �������� ���� AAA
void CTDownSpeed(void);

// ������� �������� ����� AAA
void CTUpSpeed(void);

//�������� �������� ���� AAA
void CTDownSix();

//�������� �������� ����� AAA
void CTUpSix();

//������������� AAA
void PlayTrackUnderC();

// ������ ������� ������
char GetPlayingStatus();

// ������������� ������
void SetPlayingStatus(char PS);

// ���������
unsigned short GetVolLevel();

// ��������� ��������� �� ������������� �������...
void SetPHandle(short ph);

// ���������� ���-�� ������ � ����������� ��
int GetTC();

// ������� ������   AAA
void Memory();

// ��������� ��!   AAA
void SavePlaylist(char *fn);

// ��������� ������ � ��   AAA
void PastLine(WSHDR *p, unsigned short i);

// �������� ������ � ��   AAA
void CopyLine(WSHDR *p);

// ������� ������ �� ��   AAA
void DeleteLine();

// ���������� ������ � �� �����   AAA
void MoveLineUp();

// ���������� ������ � �� ����   AAA
void MoveLineDown();

// ���������� ������ � ��������� ��   AAA
void MoveLineRight();

// ���������� ������ � ���������� ��   AAA
void MoveLineLeft();

// ������� �������� ������ (������ � ��������� �� WSHDR)   AAA
void fix(char* p);

// ����������� ���� �� ������ � ��
WSHDR * GetCurrentTrack();

// ����������� �������� ���� �� ������ � ��
WSHDR * GetPlayedTrack();

// �����������
void PL_Redraw(WSHDR** mass, int* CurLine, int* MarkLine, unsigned int* AllLines, int CurList, int MarkList);

// ������ ���������   AAA
void BandRoll(int CurLine, int AllLines);

//���� ����� � �����   AAA
//void FindMusic(const char *dir, int i);

// ��� �������� �� �� �������� ������
void LoadingPlaylist(const char * fn);

// ������ ����� �� �����. �������
void LoadingDaemonList(const char* path);

// ������ ������ � ����� ���� �������...   AAA
void MemoryFree();

#endif
