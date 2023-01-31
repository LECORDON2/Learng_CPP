// Windows_API_Lecture.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hWnd;                               // 메인 윈도우 핸들
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

    // Core 초기화
    if (FAILED(CCore::Getinst()->init(g_hWnd, POINT{1280, 768})))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 윈도우 메세지 기반 방식은 입력이 없으면 돌아가지 않는다.
    // 윈도우 메세지 기반 방식으로 강제로 프로그램을 지속적으로 돌리는 방법은 아래와 같다.
    // 그러나 굉장히 비효율적
    // SetTimer(g_hWnd, 10, 0, nullptr);  // (윈도우 핸들, 타이머 ID, 처리속도(0은 최대), 함수 호출)

    // GetMessage
    // 메세지 큐에서 메세지 확인 될 때까지 대기 // 큐 = 선입선출
    // msg.message == WM_QUIT 인 경우 false 를 만환 -> 프로그램 종료

    // PeekMessage
    // 메세지 유무와 관계없이 반환
    // 메세지가 있으면 true 없으면 false
    // 메세지 큐에서 메세지를 확인한 경우 true, 메세지 큐에서 메세지가 없는 경우 false를 반환한다.

    // 기본 메시지 루프입니다:
    while (true) 
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 마지막 옵션은 보고 제거할지 말지에 대한 것
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 메세지가 없는 동안 호출
            CCore::Getinst()->progress();

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

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   // 윈도우는 O.S가 관리하는 Curnel object를 가진다.
   // 이는 운영체제가 관리하는 오브젝트라서 객체에 대한 접근과 관리가 힘들다.
   // 그래스 윈도우는 ID를 제공한다. 이것을 윈도우 핸들이라고 한다.
   // 이러한 ID와 함수 등을 이용하여 관리한다. 
   // hWnd는 핸들

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

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

#include <vector>

using std::vector;

struct tObjInfo
{
    POINT g_ptObjectPos;
    POINT g_ptObjectScale;
};

vector<tObjInfo> g_vecInfo;

// 좌 상단
POINT g_ptLT;

// 우 하단
POINT g_ptRB;

bool bLbtnDown = false;

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

            // 직접 펜과 브러쉬 만들어서 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
            // HBRUSH hBlueBrush = GetStockObject(); 
            // GetStockObject 미리 만들어져 있는 자주 쓰는 기능을 가져오는 함수, 내가 만든 것이 아니므로 지우면 안됨 

            // RGB = ((COLORREF)(((BYTE)(r) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(b)) << 16)))
            // 비트 연산을 통해서 3바이트 구조에 RGB를 넣는다.

            // 기존 펜과 브러쉬 ID 값을 받아 둠
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);        
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush); 
            // hdc에게 우리가 만든 펜을 함수를 통해서 준다
            // 그러나 SelectObject는 void* 이기 때문에 강제로 캐스팅 한다.

            // 변경된 펜과 브러쉬로 사각형 그림

            if (bLbtnDown)
            {
                Rectangle(hdc
                    , g_ptLT.x
                    , g_ptLT.y
                    , g_ptRB.x
                    , g_ptRB.y);
            }

            // 추가된 사각형 들도 그려준다.
            for (size_t i = 0; i < g_vecInfo.size(); ++ i)
            {
                Rectangle(hdc
                    , g_vecInfo[i].g_ptObjectPos.x - g_vecInfo[i].g_ptObjectScale.x / 2
                    , g_vecInfo[i].g_ptObjectPos.y - g_vecInfo[i].g_ptObjectScale.y / 2
                    , g_vecInfo[i].g_ptObjectPos.x + g_vecInfo[i].g_ptObjectScale.x / 2
                    , g_vecInfo[i].g_ptObjectPos.y + g_vecInfo[i].g_ptObjectScale.y / 2);
            }


            // DC의 펜과 브러쉬를 원래 펜으로 되돌림
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다쓴 펜과 브러쉬 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);

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

            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN: // 키가 누린 경우의 케이스
    {
        switch (wParam) // wParam는 키눌림에 대한 추가 정보
        {
        case VK_UP: // VK_UP는 방향키 위
            // g_ptObjectPos.y -=10;
            InvalidateRect(hWnd, nullptr, true); // 무효와 영역을 직접 설정, nullptr은 전체 영역, true는 무효화 영역을 발생시키면서 기존의 영역에 있던 데이터를 지워버리는 것
            break;

        case VK_DOWN:
            // g_ptObjectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_LEFT:
            // g_ptObjectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
            // g_ptObjectPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        // case 'W':  // 키보드 영문 쪽 키는 아스키 코드로 체크를 한다.
        // {
        //     int a = 0;
        // }
        //     break;

        }
    }
        break;

    case WM_LBUTTONDOWN: // 마우스 좌클릭
    {
        // LOWORD(lParam); // x 좌표
        // HIWORD(lParam); // y 좌표
        // lParam 
        // lParam은 마우스에 대한 추가 정보, 마우스 좌표가 들어 옴
        // 4byte 자료형 이며 2byte 씩 나누어 x, y 좌표를 표현
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtnDown = true;
    }
        break;

    case WM_MOUSEMOVE:
    {
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
    }
        break;

    case WM_LBUTTONUP: 
    {
        tObjInfo info = {};
        info.g_ptObjectPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjectPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjectScale.x = abs(g_ptLT.x - g_ptRB.x); // 절댓값 함수
        info.g_ptObjectScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);

        bLbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
        break;

    case WM_TIMER:
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
