#ifndef _PLAYLIST_H_
  #define _PLAYLIST_H_

// ��������� ��� ����� ��������� ��� � ������������� ����... � �� ����� ����������! :D
void DisableScroll(void);

// ��������� ���������
void VolumeUp();

// �������� ���������
void VolumeDown();

// ��������� �� ����
void ToggleVolume();

// ��������� ����
void RandTrack();

//������������� ����
void RepeatTrack();

// ��� plamode==1
void NextTrackX();

// ��������� ���� ��
void NextTrack();

// ���������� ���� ��
void PreviousTrack();

// �����/���������������
void TogglePlayback();

// ������������� ������������
void StopAllPlayback();

// ������������� ��� ����������� ����� AAA
void CTandPTtoFirst();

//������� �������� ���� AAA
void CTDown();

//������� �������� ����� AAA
void CTUp();

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
unsigned int GetVolLevel();

// ��������� ��������� �� ������������� �������...
void SetPHandle(short ph);

// ���������� ���-�� ������ � ����������� ��
int GetTC();

// ���������� ��������� mp3-����
int GetMP3Tag_v1(const char * fname, MP3Tagv1 * tag);

// ��� �������� �� �� �������� ������
void LoadingPlaylist(const char * fn);

// ������� ��!
void FreePlaylist(void);

// ��������� ��!
int LoadPlaylist(const char * fn);

//��������� ��!   AAA
void SavePlaylist(char *fn);

// ����������� ���� �� ������ � ��
char * GetCurrentTrack();

// ����������� �������� ���� �� ������ � ��
char * GetPlayedTrack();

// ���������� �����-������
char * Lighten(char * source);

// �����������
void PL_Redraw();

#endif
