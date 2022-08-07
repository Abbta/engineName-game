#include "MainWindow.h"
#pragma once
namespace EngineName
{
	namespace Base
	{
		/*
		* Width and Height classes
		* bridge between coordinates inside engine to the output coordinates sent to winapi
		* (coordinates sent to winapi is always pixels in the mainwindow, while coordinates inside is not necessarily that)
		* contains width/height of output area from engine's perspective
		* contains ref to mainwindow, gives access to width/height of the actual window from windows' perspective
		* contains functions for transforming an arbitrary width inside engine to width pixels in window
		* 
		* TODO: make classes support different kinds of lengths, for example those who don't change when windowsize changes
		*/
		class Width
		{
		private:
			//width for reference to constant width lengths
			td_width mp_width;

			//ref to mainwindow
			MainWindow& mp_mainWinRef;
		public:
			Width(MainWindow& mainWindow);
			//get width of output
			operator const td_width() const { return mp_width; }
			//assign width of output
			Width& operator=(const td_width newWidth);
			//transform to winapi width (pixels in window)
			const FLOAT toOutputWidth(const td_width width) const {return toOutputWidth(static_cast<double>(width));}
			const FLOAT toOutputWidth(const signed int width) const { return toOutputWidth(static_cast<double>(width)); }
			const FLOAT toOutputWidth(const double width) const;
			//transform from winapi width
			const unsigned int fromInputWidth(const FLOAT inputWidth) const;
		};

		//exactly the same as width
		class Height
		{
		private:
			td_height mp_height;
			MainWindow& mp_mainWinRef;
		public:
			Height(MainWindow& mainWindow);

			operator const td_height() const { return mp_height; }
			Height& operator=(const td_height newHeight);
			const FLOAT toOutputHeight(const td_height height) const { return toOutputHeight(static_cast<double>(height)); }
			const FLOAT toOutputHeight(const signed int height) const { return toOutputHeight(static_cast<double>(height)); }
			const FLOAT toOutputHeight(const double height) const;
			const unsigned int fromInputHeight(const short inputHeight) const;
		};
	}
}