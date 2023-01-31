// Windows_API_Lecture.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.   // wchar_t를 WCHAR로 재정의 한 것
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 실행 된 프로세스의 시작 주소
    _In_opt_ HINSTANCE hPrevInstance,                   // 이전 프로세스의 시작 주소(초창기의 윈도우 작동 방식, 지금은 아니다), 
                                                        // 윈도우는 가상의 메모리를 사용하고 여러개의 프로그램이 실행되도 같은 주소를 가지고 있다.
                                                        // 각각의 가상 메모리 내에서의 주소를 말하는 것, 실상 물리적인 주소는 다를 수 있다. 
    _In_ LPWSTR    lpCmdLine,          // 윈도우 명령 프롬프트로 문자열을 넣으면 실행 할 수 있다.
    _In_ int       nCmdShow)

                                              // _In_(입력된다), _In_opt_(부가적인 in) 등은 SAL 주석이라고 부르는 것, 
{                                             // 실제로는 무시되는 것, 해당코드의 용도를 적어놓은 것
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);  // 리소스 뷰 string table에 IDS_APP_TITLE이 존재함(프로젝트 이름의 디폴드 값)
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // GetMessage
    // 메세지 큐에서 메세지 확인 될 때까지 대기 // 큐 = 선입선출
    // msg.message == WM_QUIT 인 경우 false 를 만환 -> 프로그램 종료

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   // 윈도우는 O.S가 관리하는 Curnel object를 가진다.
   // 이는 운영체제가 관리하는 오브젝트라서 객체에 대한 접근과 관리가 힘들다.
   // 그래스 윈도우는 ID를 제공한다. 이것을 윈도우 핸들이라고 한다.
   // 이러한 ID와 함수 등을 이용하여 관리한다. 
   // hWnd는 핸들

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:   // 무효화 영역(Invalidate)(ex : 최소화)이 발생한 경우 WM_PAINT를 발생시킴
        {            // switch case 내부에서 변수 선언하려면 괄호가 필요하다.
            
            PAINTSTRUCT ps;
            
            // Divice Context 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps); // Divice Context(그리기), hdc도 윈도우 핸들
            // DC(Divice Context)의 목적지는 hㅉnd
            // DC 의 펜은 기본펜(Black)
            // DC의 브러쉬는 기본 브러쉬(White)
            // Divice Context는 그리기 작업 수행에 필요한 data 집합이다.
            // Pixel은 R.G.B로 구성되어 있고 1byte 씩 지정되어 있다(Pixel 하나당 3byte)

            // 직접 펜을 만들어서 DC에 지급

            // HDC 구조체의 모습
            // struct _HDC
            // {
            //     int a; a에는 ID값이 들어 감
            // }typedef HDC;
            // 각각의 핸들을 구분하기 위해 다른 구조체를 사용함

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 윈도우 핸들
            
            // 윈도우 좌표
            // 작업 영역(타이틀, 메뉴바 밑) 좌 상단이 (0, 0), 1단위는 pixel단위
             
            // HDC

            Rectangle(hdc, 10 ,10, 110, 110); 

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
