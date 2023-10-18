/** \file eventTests.cpp */
#include "eventTests.h"

namespace EventTests
{
	TEST(WinClose, callback)
	{
		init();

		bool before = callbackChecks[0];

		Engine::WindowCloseEvent e;
		auto& callback = handler->getOnWindowClose();
		callback(e);

		bool after = callbackChecks[0];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinClose, handle)
	{
		init();

		Engine::WindowCloseEvent e;
		bool before = e.handled();

		auto& callback = handler->getOnWindowClose();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinResize, callback)
	{
		init();

		bool before = callbackChecks[1];

		Engine::WindowResizeEvent e(1080, 720);
		auto& callback = handler->getOnWindowResize();
		callback(e);

		bool after = callbackChecks[1];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinResize, handle)
	{
		init();

		Engine::WindowResizeEvent e(1080, 720);
		bool before = e.handled();

		auto& callback = handler->getOnWindowResize();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}
	
	TEST(WinResize, data) 
	{
		init();

		Engine::WindowResizeEvent e(1080, 720);
		
		int32_t height = e.getHeight();
		int32_t width = e.getWidth();

		EXPECT_EQ(height, 720);
		EXPECT_EQ(width, 1080);
	}

	TEST(WinFocus, callback)
	{
		init();

		bool before = callbackChecks[2];

		Engine::WindowFocusEvent e;
		auto& callback = handler->getOnWindowFocus();
		callback(e);

		bool after = callbackChecks[2];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinFocus, handle)
	{
		init();

		Engine::WindowFocusEvent e;
		bool before = e.handled();

		auto& callback = handler->getOnWindowFocus();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinLoseFocus, callback)
	{
		init();

		bool before = callbackChecks[3];

		Engine::WindowLoseFocusEvent e;
		auto& callback = handler->getOnWindowLoseFocus();
		callback(e);

		bool after = callbackChecks[3];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinLoseFocus, handle)
	{
		init();

		Engine::WindowLoseFocusEvent e;
		bool before = e.handled();

		auto& callback = handler->getOnWindowLoseFocus();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinMove, callback)
	{
		init();

		bool before = callbackChecks[4];

		Engine::WindowMoveEvent e(500, 120);
		auto& callback = handler->getOnWindowMove();
		callback(e);

		bool after = callbackChecks[4];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinMove, handle)
	{
		init();

		Engine::WindowMoveEvent e(500, 120);
		bool before = e.handled();

		auto& callback = handler->getOnWindowMove();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(WinMove, data)
	{
		init();

		Engine::WindowMoveEvent e(500, 120);

		int32_t xPos = e.getNewXPos();
		int32_t yPos = e.getNewYPos();

		EXPECT_EQ(xPos, 500);
		EXPECT_EQ(yPos, 120);
	}

	TEST(KeyPress, callback)
	{
		init();

		bool before = callbackChecks[5];

		Engine::KeyPressEvent e(52, 3);
		auto& callback = handler->getOnKeyPress();
		callback(e);

		bool after = callbackChecks[5];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(KeyPress, handle)
	{
		init();

		Engine::KeyPressEvent e(52, 3);
		bool before = e.handled();

		auto& callback = handler->getOnKeyPress();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(KeyPress, data)
	{
		init();

		Engine::KeyPressEvent e(52, 3);

		int32_t keyCode = e.getKeyCode();
		int32_t repeatCount = e.getRepeatCount();

		EXPECT_EQ(keyCode, 52);
		EXPECT_EQ(repeatCount, 3);
	}

	TEST(KeyRelease, callback)
	{
		init();

		bool before = callbackChecks[6];

		Engine::KeyReleaseEvent e(14);
		auto& callback = handler->getOnKeyRelease();
		callback(e);

		bool after = callbackChecks[6];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(KeyRelease, handle)
	{
		init();

		Engine::KeyReleaseEvent e(14);
		bool before = e.handled();

		auto& callback = handler->getOnKeyRelease();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(KeyRelease, data)
	{
		init();

		Engine::KeyReleaseEvent e(14);

		int32_t keyCode = e.getKeyCode();

		EXPECT_EQ(keyCode, 14);
	}

	TEST(KeyType, callback)
	{
		init();

		bool before = callbackChecks[7];

		Engine::KeyTypeEvent e(31);
		auto& callback = handler->getOnKeyType();
		callback(e);

		bool after = callbackChecks[7];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(KeyType, handle)
	{
		init();

		Engine::KeyTypeEvent e(31);
		bool before = e.handled();

		auto& callback = handler->getOnKeyType();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(KeyType, data)
	{
		init();

		Engine::KeyTypeEvent e(31);

		int32_t keyCode = e.getKeyCode();

		EXPECT_EQ(keyCode, 31);
	}

	TEST(MouseButtonPress, callback)
	{
		init();

		bool before = callbackChecks[8];

		Engine::MouseButtonPressEvent e(0);
		auto& callback = handler->getOnMouseButtonPress();
		callback(e);

		bool after = callbackChecks[8];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseButtonPress, handle)
	{
		init();

		Engine::MouseButtonPressEvent e(0);
		bool before = e.handled();

		auto& callback = handler->getOnMouseButtonPress();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseButtonPress, data)
	{
		init();

		Engine::MouseButtonPressEvent e(1);

		int32_t button = e.getButton();

		EXPECT_EQ(button, 1);
	}

	TEST(MouseButtonRelease, callback)
	{
		init();

		bool before = callbackChecks[9];

		Engine::MouseButtonReleaseEvent e(0);
		auto& callback = handler->getOnMouseButtonRelease();
		callback(e);

		bool after = callbackChecks[9];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseButtonRelease, handle)
	{
		init();

		Engine::MouseButtonReleaseEvent e(0);
		bool before = e.handled();

		auto& callback = handler->getOnMouseButtonRelease();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseButtonRelease, data)
	{
		init();

		Engine::MouseButtonReleaseEvent e(1);

		int32_t button = e.getButton();

		EXPECT_EQ(button, 1);
	}

	TEST(MouseMove, callback)
	{
		init();

		bool before = callbackChecks[10];

		Engine::MouseMoveEvent e(45, 108);
		auto& callback = handler->getOnMouseMove();
		callback(e);

		bool after = callbackChecks[10];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseMove, handle)
	{
		init();

		Engine::MouseMoveEvent e(45, 108);
		bool before = e.handled();

		auto& callback = handler->getOnMouseMove();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseMove, data)
	{
		init();

		Engine::MouseMoveEvent e(206, 31);

		int32_t mouseX = e.getNewXPos();
		int32_t mouseY = e.getNewYPos();

		EXPECT_EQ(mouseX, 206);
		EXPECT_EQ(mouseY, 31);
	}

	TEST(MouseScroll, callback)
	{
		init();

		bool before = callbackChecks[11];

		Engine::MouseScrollEvent e(50);
		auto& callback = handler->getOnMouseScroll();
		callback(e);

		bool after = callbackChecks[11];
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseScroll, handle)
	{
		init();

		Engine::MouseScrollEvent e(50);
		bool before = e.handled();

		auto& callback = handler->getOnMouseScroll();
		callback(e);

		bool after = e.handled();
		EXPECT_FALSE(before);
		EXPECT_TRUE(after);

	}

	TEST(MouseScroll, data)
	{
		init();

		Engine::MouseScrollEvent e(62);

		int32_t offset = e.getOffset();

		EXPECT_EQ(offset, 62);

	}
}