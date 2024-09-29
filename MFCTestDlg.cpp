
// MFCTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "afxdialogex.h"
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define default_ratio 100
#define START_POS 1
#define FINISH_POS 2
#define MOVE_RATIO 20
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTestDlg 대화 상자



CMFCTestDlg::CMFCTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_CONTROL, m_image_control);
	DDX_Control(pDX, IDC_TXT_CIRCLE, m_num_circles);
	DDX_Control(pDX, IDC_START_POS_EDIT, Start_pos_x_y);
	DDX_Control(pDX, IDC_FINISH_POS_EDIT, finish_pos_x_y);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMFCTestDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMFCTestDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCTestDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_GENERATION, &CMFCTestDlg::OnBnClickedBtnGeneration)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CMFCTestDlg::OnBnClickedBtnQuit)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCTestDlg::OnBnClickedBtnDraw)
	ON_WM_GETMINMAXINFO()
//	ON_WM_SIZE()
ON_WM_SIZING()
//ON_WM_SIZE()
ON_WM_ERASEBKGND()

END_MESSAGE_MAP()


// CMFCTestDlg 메시지 처리기

BOOL CMFCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	dynamicLayoutSetup();

	GetClientRect(&initRect);
	CalcWindowRect(initRect);
	nSttX = nSttY = nFinX = nFinY = nRadius = nX = nY = index = nGray = 0;
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTestDlg::dynamicLayoutSetup() {
	this->EnableDynamicLayout();

	auto m_none = CMFCDynamicLayout::MoveSettings{};
	auto m_only_x = CMFCDynamicLayout::MoveSettings{};	m_only_x.m_nXRatio = default_ratio;
	auto m_only_y = CMFCDynamicLayout::MoveSettings{};	m_only_y.m_nYRatio = default_ratio;
	auto m_both = CMFCDynamicLayout::MoveSettings{};	m_both.m_nXRatio = m_both.m_nYRatio = default_ratio;


	auto s_none = CMFCDynamicLayout::SizeSettings{};
	auto s_only_x = CMFCDynamicLayout::SizeSettings{};	s_only_x.m_nXRatio = default_ratio;
	auto s_only_y = CMFCDynamicLayout::SizeSettings{};	s_only_y.m_nYRatio = default_ratio;
	auto s_both = CMFCDynamicLayout::SizeSettings{};	s_both.m_nXRatio = s_both.m_nYRatio = default_ratio;

	auto layoutPointer = this->GetDynamicLayout();
	layoutPointer->Create(this);

	layoutPointer->AddItem(IDC_BTN_ACTION, m_none, s_none);
	layoutPointer->AddItem(IDC_BTN_GENERATION, m_none, s_none);
	layoutPointer->AddItem(IDC_BTN_LOAD, m_none, s_none);
	layoutPointer->AddItem(IDC_BTN_SAVE, m_none, s_none);
	layoutPointer->AddItem(IDC_BTN_IMAGE, m_none, s_none);

	layoutPointer->AddItem(IDC_FINISH_POS_EDIT, m_none, s_none);
	layoutPointer->AddItem(IDC_START_POS_EDIT, m_none, s_none);
	layoutPointer->AddItem(IDC_TXT_CIRCLE, m_none, s_none);

	layoutPointer->AddItem(IDC_PIC_CONTROL, m_none, s_both);
	
}

void CMFCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCTestDlg::ImageGen(int nWidth, int nHeight, int nBpp) {
	if (m_image != NULL) {
		m_image.Destroy();
		m_image.Create(nWidth, -nHeight, nBpp);
	}
	else {
		m_image.Create(nWidth, -nHeight, nBpp);
	}

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; ++i) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}
}	

CString CMFCTestDlg::explorerOpen(int mod) {
	CString str_filter = _T("All files(*.*)|*.*|image file (*.bmp) | *.bmp|image file (*.jpg, *.jpeg) | *.jpg, *.jpeg|");

	CFileDialog f_dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str_filter, this);
	BOOL isOK = TRUE;

	do {
		if (f_dlg.DoModal() == IDOK) {
			if ((f_dlg.GetFileExt() == _T("bmp")) || (f_dlg.GetFileExt() == _T("jpg")) || (f_dlg.GetFileExt() == _T("jpeg"))) {
				return f_dlg.GetPathName();
			}
			else {
				AfxMessageBox(_T("잘못된 파일입니다."));
			}
		}
		else {
			return _T("WRONG_PATH");
		}
	} while (isOK);
}

void CMFCTestDlg::OnBnClickedBtnSave()
{
	CString path = explorerOpen(IDC_BTN_SAVE);

	if (path.Compare(_T("WRONG_PATH"))) {
		m_image.Save(path);
	}
}


void CMFCTestDlg::OnBnClickedBtnLoad()
{
	CheckAndDestroy();

	CString path = explorerOpen(IDC_BTN_LOAD);

	if (path.Compare(_T("WRONG_PATH"))) {
		m_image.Load(path);

		HDC hdc = m_image.GetDC();
		unsigned char* fm = (unsigned char*)m_image.GetBits();
		int nWidth = m_image.GetWidth();
		int nHeight = m_image.GetHeight();
		int nPitch = m_image.GetPitch();
		double dCenterX = 0.0, dCenterY = 0.0;

		CalculateCenter(fm, nWidth, nHeight, nPitch, &dCenterX, &dCenterY);
		DrawPositionLine(fm, nWidth, nHeight, nPitch, dCenterX, dCenterY);
		DrawPositionCross(fm, nWidth, nHeight, nPitch, dCenterX, dCenterY);

		CString pos;
		pos.Format(_T("%.3lf, %.3lf"), dCenterX, dCenterY);
		TextOut(hdc, dCenterX, dCenterY, pos, pos.GetLength());

		UpdataeDisplay(m_image.GetWidth(), m_image.GetHeight());
	}
}

void CMFCTestDlg::UpdataeDisplay(int nWidth, int nHeight) {
	CDC* dc = m_image_control.GetDC();
	m_image.StretchBlt(dc->m_hDC, 0, 0, nWidth, nHeight, SRCCOPY);
}

void CMFCTestDlg::CheckAndDestroy() {
	if (m_image != NULL) {
		m_image.Destroy();
	}
}

void CMFCTestDlg::DrawCircle(unsigned char* fm, int x, int y, int nGray, int nRadius) {
	int nCenterX = x;
	int nCenterY = y;
	int nPitch = m_image.GetPitch();

	for (int j = y-nRadius; j < y + (nRadius); ++j) {
		for (int i = x-nRadius; i < x + (nRadius); ++i) {
			
			if(isInCircle(i, j, nCenterX, nCenterY, nRadius)) {
				fm[j * nPitch + i] = nGray;
			}
		}
	}
}

int intRand(int min, int max) {
	thread_local std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

#include <thread>

void CMFCTestDlg::GenerateCircle(unsigned char* fm, int nCircles, int nWidth, int nHeight, int nPitch) {
	int nRadius = intRand(10, 100);
	int x = intRand(0, nWidth - (nRadius << 1));
	int y = intRand(0, nHeight - (nRadius << 1));
	int nGray = intRand(0x28, 0xA0);
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;

	for (int j = y; j < y + (nRadius << 1); ++j) {
		for (int i = x; i < x + (nRadius << 1); ++i) {

			if (isInCircleThread(i, j, nCenterX, nCenterY, nRadius)) {
				fm[j * nPitch + i] = nGray;
			}
		}
	}
}

BOOL CMFCTestDlg::isInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius) {
	double rad = (double)pow((double)(x - nCenterX), 2) + (double)pow((double)(y - nCenterY), 2);

	return (rad < (nRadius * nRadius));
}

BOOL CMFCTestDlg::isInCircleThread(int x, int y, int nCenterX, int nCenterY, int nRadius) {
	double dX = x - nCenterX;
	double dY = y - nCenterY;
	
	double rad = dX * dX + dY * dY;

	return (rad < (nRadius * nRadius));
}

CString CMFCTestDlg::GetTextGenerationCircles() {
	CString str;
	m_num_circles.GetWindowTextW(str);
	return str;
}

void CMFCTestDlg::DrawPositionLine(unsigned char* fm, int nWidth, int nHeight, int nPitch, double dCenterX, double dCenterY) {

	for (int j = dCenterY; j >= 0; j -= 4) {
		fm[j * nPitch + (int)dCenterX] = 0xff;
	}

	for (int i = dCenterX; i >= 0; i -= 4) {
		fm[(int)dCenterY * nPitch + i] = 0xff;
	}
}

void CMFCTestDlg::DrawPositionCross(unsigned char* fm, int nWidth, int nHeight, int nPitch, double dCenterX, double dCenterY) {
	for (int j = 0; j < 10; ++j) {
		for (int i = 0; i < 10; ++i) {
			if (i == j) {
				fm[(j + (int)dCenterY - 5) * nPitch + (i + (int)dCenterX - 5)] = 0x00;
			}
		}
	}

	for (int j = 0; j < 10; ++j) {
		for (int i = 9; i >= 0; --i) {
			if ((i + j) == 9) {
				fm[(j + (int)dCenterY - 5) * nPitch + (i + (int)dCenterX - 5)] = 0x00;
			}
		}
	}
}

void CMFCTestDlg::CalculateCenter(unsigned char* fm, int nWidth, int nHeight, int nPitch, double* dCenterX, double* dCenterY) {
	CRect rect(0, 0, nWidth, nHeight);

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > 10) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	*dCenterX = (double)nSumX / nCount;
	*dCenterY = (double)nSumY / nCount;
}

void CMFCTestDlg::OnBnClickedBtnGeneration()
{
	CRect rect = GetRect();
	CDC* dc = GetCDCPointer(rect);

	int nWidth = (m_image != NULL) ? m_image.GetWidth() : rect.Width();
	int nHeight = (m_image != NULL) ? m_image.GetHeight() : rect.Height();
	int nBpp = 8;
	ImageGen(nWidth, nHeight, nBpp);

	int nCircles = 0;
	int nThreads = 0;

	nCircles = _ttoi(GetTextGenerationCircles());
	nThreads = nCircles;
	int circlePerThread = nCircles / nThreads;

	
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	unsigned char** fmList = new unsigned char* [nCircles];

	for (int i = 0; i < nCircles; ++i) {
		fmList[i] = new unsigned char[nWidth * nHeight];
		memset((void*)*(fmList + i), 0x00, sizeof(unsigned char) * nWidth * nHeight);
	}

	std::thread *threadArr = new std::thread[nThreads];
	for (int i = 0; i < nThreads; ++i) {
		threadArr[i] = std::thread(GenerateCircle, fmList[i], nCircles, nWidth, nHeight, nPitch);
	}
	for (int i = 0; i < nThreads; ++i) {
		threadArr[i].join();
	}

	for (int i = 0; i < nCircles; ++i) {
		memcpy(fm, fmList[i], sizeof(unsigned char) * nWidth * nHeight);

		CString pos;
		
		UpdataeDisplay(nWidth, nHeight);
		pos.Format(_T(".\\circle%d.bmp"), i+1);
		m_image.Save(pos);

		free(fmList[i]);
	}
}


void CMFCTestDlg::OnBnClickedBtnQuit()
{
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_APP_EXIT, NULL);
}


void CMFCTestDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialogEx::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize.x = initRect.Width();
	lpMMI->ptMinTrackSize.y = initRect.Height();
}

CDC* CMFCTestDlg::GetCDCPointer(CRect rc) {
	m_image_control.GetClientRect(rc);
	CDC* dc = m_image_control.GetDC();
	return dc;
}

CRect CMFCTestDlg::GetRect() {
	CRect rect;
	m_image_control.GetClientRect(rect);
	return rect;
}

void CMFCTestDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	if (m_image != NULL) {
		CRect rect = GetRect();
		CDC* dc = GetCDCPointer(rect);
		m_image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	}
}

BOOL CMFCTestDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_image != NULL) {
		CMFCTestDlg::OnPaint();

		CRect rect = GetRect();
		CDC* dc = GetCDCPointer(rect);
		UpdataeDisplay(rect.Width(), rect.Height());
		return FALSE;
	}
	else {
		return CDialogEx::OnEraseBkgnd(pDC);
	}
}

CString CMFCTestDlg::GetTextPosition(int mode) {
	CString str;
	if (mode == 1)
		Start_pos_x_y.GetWindowTextW(str);
	else
		finish_pos_x_y.GetWindowTextW(str);
	return str;
}

void CMFCTestDlg::PositionTokenizer(CString str, int *x, int *y) {
	CString token;
	int pos = 0;
	int index = 0;

	while ((token = str.Tokenize(_T(","), pos)) != _T("")) {
		if (index == 0) {
			*x = _ttoi(token);
			index++;
			
		}
		else if (index == 1) {
			*y = _ttoi(token);
			index++;
		}
		else {
			break;
		}
	}
}

void CMFCTestDlg::OnBnClickedBtnDraw()
{
	CRect rect = GetRect();
	CDC* dc = GetCDCPointer(rect);
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	int nBpp = 8;
	
	nGray = intRand(0x20, 0xCB);

	CheckAndDestroy();
	ImageGen(nWidth, nHeight, nBpp);

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset((void*)fm, 0x0, nWidth * nHeight);
	UpdataeDisplay(nWidth, nHeight);

	nSttX = nSttY = 0;
	PositionTokenizer(GetTextPosition(START_POS), &nSttX, &nSttY);
	nX = nSttX;
	nY = nSttY;

	int max = (nSttX >= nSttY) ? nSttY : nSttX;
	nRadius = intRand(2, max);

	DrawCircle(fm, nSttX, nSttY, nGray, nRadius);
}

BOOL CMFCTestDlg::validImagePos(int x, int y, int radius) {
	return ((x + radius) > m_image.GetWidth()) || ((y + radius) > m_image.GetHeight()) || ((y - radius) <= 0) || ((x - radius) <= 0);
}

void CMFCTestDlg::MoveRect() {
	//int nGray = 80;
	int mX = (nFinX - nSttX) / MOVE_RATIO;
	int mY = (nFinY - nSttY) / MOVE_RATIO;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	
	memset(fm, 0x0, nWidth * nHeight);

	nX = nX + mX;
	nY = nY + mY;
	DrawCircle(fm, nX, nY, nGray, nRadius);
	UpdataeDisplay(nWidth, nHeight);
}

void CMFCTestDlg::OnBnClickedBtnAction()
{
	int mX = (nFinX - nSttX) / MOVE_RATIO;
	int mY = (nFinY - nSttY) / MOVE_RATIO;
	PositionTokenizer(GetTextPosition(FINISH_POS), &nFinX, &nFinY);

	if (!validImagePos(nX, nY, nRadius)) {
		MoveRect();
		CString pos;
		pos.Format(_T(".\\move_circle%d.bmp"), index++);
		m_image.Save(pos);
	}
	else {
		MessageBox(L"더 이상 움직일 수 없습니다.", L"경고", MB_OK | MB_ICONERROR);
	}
}
