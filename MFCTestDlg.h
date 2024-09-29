
// MFCTestDlg.h: 헤더 파일
//

#pragma once


// CMFCTestDlg 대화 상자
class CMFCTestDlg : public CDialogEx
{
private:
	CImage m_image;
	int nX, nY;
	int nSttX, nSttY;
	int nFinX, nFinY;
	int index;
	int nRadius;
	int nGray;
	CRect initRect;
	BOOL validImagePos(int x, int y, int radius);
	BOOL isInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius);
	static BOOL isInCircleThread(int x, int y, int nCenterX, int nCenterY, int nRadius);
// 생성입니다.
public:
	CMFCTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//변수
	CStatic m_image_control;

//동적 레이아웃 함수
	void dynamicLayoutSetup();

//이벤트 함수
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnGeneration();
	afx_msg void OnBnClickedBtnAction();

//이벤트 처리 함수
	void UpdataeDisplay(int nWidth, int nHeight);
	void CheckAndDestroy();
	void MoveRect();
	void DrawCircle(unsigned char* fm, int x, int y, int nGray, int nRadius);
	void ImageGen(int nWidth, int nHeight, int nBpp);
	static void GenerateCircle(unsigned char* fm, int nCircles, int nWidth, int nHeight, int nPitch);
	void DrawPositionLine(unsigned char* fm, int nWidth, int nHeight, int nPitch, double dCenterX, double dCenterY);
	void DrawPositionCross(unsigned char* fm, int nWidth, int nHeight, int nPitch, double dCenterX, double dCenterY);
	void CalculateCenter(unsigned char* fm, int nWidth, int nHeight, int nPitch, double *dCenterX, double *dCenterY);
	void PositionTokenizer(CString str, int* x, int* y);
	CString GetTextGenerationCircles();
	CString GetTextPosition(int mode);
	CDC* GetCDCPointer(CRect rc);
	CRect GetRect();
	CString explorerOpen(int mod);
	CEdit m_num_circles;
	CEdit Start_pos_x_y;
	CEdit finish_pos_x_y;
	afx_msg void OnBnClickedBtnQuit();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
