/*!
 * \file draw.h
 * \author Hekar Khani, Samuel Lewis, Adrian Hyde, Dan Evans
 * \date December 8, 2010
 * \description Supporting functions for drawing
 *	on the RTOS #4 Windows test application
 */

#ifndef DRAW_H
#define DRAW_H

#pragma warning ( disable : 4996 )

/*!
 *
 * \brief
 * This is the Window Procedure for the main window of this application.
 * It processes all messages destined for this main window.
 *
 * \param HWND hwnd - Handle to window to draw on
 * \param HDC hdc - HDC to perform painting
 * \param T *cirbuffer - Circular buffer to draw to screen
 * \param T head - Head of the buffer
 * \param T tail - Tail of the buffer
 * \param unsigned int count - Size of the buffer
 * \param x - X coordinate to draw on screen
 * \param y - Y coordinate to draw on screen
 * \param w - Width to draw on screen
 * \param h - Height to draw on screen
 */
template <typename X, typename T>
void DrawCircularBuffer (HWND hwnd, HDC hdc, X *cirbuffer, T head, T tail, unsigned int count, 
		int x = 0, int y = 0, int w = 32, int h = 32)
{
	RECT bounds;
	GetClientRect (hwnd, &bounds);

	RECT rect = {x, y, x + w, y + h};
	for (unsigned int i = 0; i < count; i++)
	{
		LOGBRUSH logbrush;
		if (i == head && i == tail)
		{
			logbrush.lbHatch = BS_SOLID;
			logbrush.lbColor = GREEN;
			logbrush.lbStyle = 0;
		}
		else if (i == head)
		{
			logbrush.lbHatch = BS_SOLID;
			logbrush.lbColor = BLUE;
			logbrush.lbStyle = 0;
		}
		else if (i == tail)
		{
			logbrush.lbHatch = BS_SOLID;
			logbrush.lbColor = RED;
			logbrush.lbStyle = 0;
		}
		else
		{
			logbrush.lbHatch = BS_SOLID;
			logbrush.lbColor = GREY;
			logbrush.lbStyle = 0;
		}
		
		SetBkColor (hdc, logbrush.lbColor);

		HBRUSH brush = CreateBrushIndirect (&logbrush);
		SelectObject (hdc, brush);
		FillRect (hdc, &rect, brush);
		DeleteObject (brush);

		logbrush.lbHatch = BS_SOLID;
		logbrush.lbColor = BLACK;
		logbrush.lbStyle = 0;

		brush = CreateBrushIndirect (&logbrush);
		SelectObject (hdc, brush);

		MoveToEx (hdc, rect.right - 1, rect.top - 1, NULL);
		LineTo (hdc, rect.right - 1, rect.bottom - 1);

		DeleteObject (brush);

		char buffer[512];
		sprintf (buffer, "%d", cirbuffer [i]);

		ExtTextOut (hdc, rect.left + 1, rect.top, 0, &rect, buffer, strlen (buffer), NULL);

		rect.left += w;
		rect.right += w;

		if (rect.right > bounds.right)
		{
			rect.left = x;
			rect.right = x + w;
			rect.top += h;
			rect.bottom += h;
		}
	}
}

#endif // DRAW_H