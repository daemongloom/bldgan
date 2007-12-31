#ifndef _PLAYLIST_H_
  #define _PLAYLIST_H_

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
void CTDovnSix();

//�������� �������� ����� AAA
void CTUpSix();

//������������� AAA
void PlayTrackUnderC();

//��������� AAA
//int * TextColor(int my_x,int my_y,int c,int w,int out_ws,int i);       �� ����� �����������, ��� �������

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

// ���������� ��������� mp3-����
//int GetMP3Tag_v1(const char * fname, MP3Tagv1 * tag);

// ������� ������   AAA
void Memory();

// ��� �������� �� �� �������� ������
void LoadingPlaylist(const char * fn);

// ������� ��!
void FreePlaylist(void);

// ��������� ��!
int LoadPlaylist(const char * fn);

// ��������� ��!   AAA
void SavePlaylist(char *fn);

// ��������� ������ � ��   AAA
void PastLine(char *p);

// �������� ������ � ��   AAA
void CopyLine(char *p);

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

// ����������� ���� �� ������ � ��
char * GetCurrentTrack();

// ����������� �������� ���� �� ������ � ��
char * GetPlayedTrack();

// �����������
void PL_Redraw();

// ������ ���������   AAA
void BandRoll();

//���� ����� � �����   AAA
void FindMusic(const char *dir, int i);

// ������ ������ � ����� ���� �������...   AAA
void MemoryFree();

#endif
