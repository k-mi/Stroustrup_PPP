#include "Graph.h"

namespace Graph_lib{
	class Controller{
	public:
		virtual void on() = 0;
		virtual void off() = 0;
		virtual void set_level(int i) = 0;
		virtual void show() = 0;

	protected:
		Controller() { }
	};

	class Test_controller : public Controller{
	public:
		Test_controller(bool on, int level) : is_on(on), m_level(level) { }

		void on();
		void off();
		void set_level(int i);
		void show();

	private:
		bool is_on;
		int m_level;
	};

	void Test_controller::on() { is_on = true; }
	void Test_controller::off() { is_on = false; }
	void Test_controller::set_level(int i) { m_level = i; }
	void Test_controller::show() {
		if(is_on) cout << "on" << endl;
		else cout << "off" << endl;
		cout << "level: " << m_level << endl;
	}

	class Line_controller : public Controller{
	public:
		Line_controller(Shape& s) : m_shape(s) { }

		void on();
		void off();
		void set_level(int i);
		void show();

	private:
		Shape& m_shape;
	};

	void Line_controller::on() { m_shape.set_color(Color::visible); }
	void Line_controller::off() { m_shape.set_color(Color::invisible); }
	void Line_controller::set_level(int i) { m_shape.set_style(Line_style(Line_style::Line_style_type(m_shape.style().style()), i)); }
	void Line_controller::show() {
		if(m_shape.color().visibility()) cout << "visible" << endl;
		else cout << "invisible" << endl;
		cout << "width: " << m_shape.style().width() << endl;
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Controller");

	Circle circle(Point(300, 200), 150);
	circle.set_fill_color(Color::yellow);
	win.attach(circle);

	Test_controller tc(true, 0);
	Line_controller lc(circle);

	Controller &c1 = tc;
	Controller &c2 = lc;

	c1.show();
	c2.show();
	win.wait_for_button();

	c1.set_level(10);
	c2.set_level(10);
	c1.show();
	c2.show();
	win.wait_for_button();

	c1.off();
	c2.off();
	c1.show();
	c2.show();
	win.wait_for_button();
}