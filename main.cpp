#include <windows.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


HWND TextBox1,TextBox2,button,txt1,txt2,txt3;

/*  Make the class name into a global variable  */
char szClassName[ ] = "Sözlük Aplication";

char kayit[20],kayit2[20];
FILE *dosya;
	FILE *ingilizce;
	FILE *turkce;
	int gwtstat=0;

	char dizi1[100][20],dizi2[100][20];


	int i=0,j=0;
	char a[20],b[20];


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "SÖZLÜK",       /* Title Text */
           WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           500,                 /* The programs width */
           300,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );


           setlocale(LC_ALL,"Turkish");
           ingilizce=fopen("ingilizce.txt","w");
	turkce=fopen("türkce.txt","w");
	dosya=fopen("sözlük.txt","r");

	while(!feof(dosya)){

		fscanf(dosya,"%s %s\n",&dizi1[i],&dizi2[i]);
		i++;
	}

	for(int k=0;k<100;k++)
    for(j=k+1;j<100;j++)
    if(strcmp(dizi1[k],dizi1[j])>0)
    {
	strcpy(a,dizi1[j]);
	strcpy(b,dizi2[j]);
    strcpy(dizi1[j],dizi1[k]);
    strcpy(dizi2[j],dizi2[k]);
    strcpy(dizi1[k],a);
    strcpy(dizi2[k],b);
	}

	 for(int k=0;k<100;k++) {

	 fprintf(turkce,"%s\n",dizi1[k]);
	 fprintf(ingilizce,"%s\n",dizi2[k]);
	}

	/* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{



    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        txt1=CreateWindow("STATIC","Türkçe-Ýngilizce",WS_VISIBLE | WS_CHILD,65,20,120,25,hwnd,NULL,NULL,NULL);
        txt2=CreateWindow("STATIC","Ýngilizce-Türkçe",WS_VISIBLE | WS_CHILD,315,20,120,25,hwnd,NULL,NULL,NULL);
        txt3=CreateWindow("STATIC","Muhammed-Barýþ",WS_VISIBLE | WS_CHILD | WS_BORDER,350,230,120,20,hwnd,NULL,NULL,NULL);

        TextBox1=CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,25,60,200,25,hwnd,NULL,NULL,NULL);
        TextBox2=CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,275,60,200,25,hwnd,NULL,NULL,NULL);

        CreateWindow("BUTTON","TIKLA",WS_VISIBLE | WS_CHILD | WS_BORDER,75,100,100,30,hwnd,(HMENU) 1,NULL,NULL);
        CreateWindow("BUTTON","TIKLA",WS_VISIBLE | WS_CHILD | WS_BORDER,325,100,100,30,hwnd,(HMENU) 2,NULL,NULL);
          break;
        case WM_COMMAND:
        switch(LOWORD(wParam))
        {
            case 1:


            gwtstat=GetWindowText(TextBox1,&kayit[0],20);
            if(gwtstat==0)
            {
                ::MessageBox(hwnd,"Kelime Giriniz","HATA!!!",MB_OK);
                break;
            }

            for(int i=0;i<100;i++)
  {
  	if(strcmp(dizi1[i],kayit)==0){


  	printf("aradýgýnýz kelime %d. satýrda  bulundu\n",i+1);
  	printf("aradýgýnýz kelimenin ingilizcesi =%s \n ",dizi2[i]);
  	::MessageBox(hwnd,dizi2[i],"SONUC",MB_OK);
  	break;
  		}
}


            break;

  }


		switch(LOWORD(wParam))
        {
            case 2:

            int gwtstat=0;
            gwtstat=GetWindowText(TextBox2,&kayit2[0],20);

			if(gwtstat==0)
            {
                ::MessageBox(hwnd,"Kelime Giriniz","HATA!!!",MB_OK);
                break;
            }

            for(int i=0;i<100;i++)
  {
  	if(strcmp(dizi2[i],kayit2)==0){


  	printf("aradýgýnýz kelime %d. satýrda  bulundu\n",i+1);
  	printf("aradýgýnýz kelimenin Türkçesi =%s \n ",dizi1[i]);
  	::MessageBox(hwnd,dizi1[i],"SONUC",MB_OK);
  	break;
  		}

}

            break;
}


break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
       default:                      /* for messages that we don't deal with */
           return DefWindowProc (hwnd, message, wParam, lParam);

}
    return 0;

}


