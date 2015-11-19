#include "GUI.h"
#include "Graph.h"

namespace Graph_lib{
	class Converter_window : public Graph_lib::Window{
	public:
		Converter_window(Point xy, int w, int h, const string& title)
			: Window(xy, w, h, title),
			inbox(Point(110, 0), 100, 20, ""),
			outbox(Point(340, 0), 100, 20, ""),
			from_menu_button(Point(0, 0), 70, 20, "from", cb_from_menu),
			to_menu_button(Point(230, 0), 70, 20, "to", cb_to_menu),
			enter_button(Point(x_max() - 70, 0), 70, 20, "enter", cb_enter),
			from_kind(Point(0, 0), 70, 20, Menu::vertical, "from"),
			to_kind(Point(230, 0), 70, 20, Menu::vertical, "to"),
			from(None),
			to(None)
		{
			string filename = "rate.txt";
			ifstream ifs(filename.c_str());
			if(!ifs) error("cannot open input file");
			ifs >> rate;

			attach(inbox);
			attach(outbox);
			attach(from_menu_button);
			attach(to_menu_button);
			attach(enter_button);

			from_kind.attach(new Button(Point(x_max() - 230, 0), 70, 20, "JPY", cb_from_jpy));
			from_kind.attach(new Button(Point(x_max() - 230, 20), 70, 20, "USD", cb_from_usd));
			to_kind.attach(new Button(Point(x_max() - 230, 40), 70, 20, "JPY", cb_to_jpy));
			to_kind.attach(new Button(Point(x_max() - 230, 60), 70, 20, "USD", cb_to_usd));

			attach(from_kind);
			attach(to_kind);
			from_kind.hide();
			to_kind.hide();
		}

	private:
		// 通貨
		enum Currency{
			None, JPY, USD
		};

		In_box inbox;
		Out_box outbox;
		Button from_menu_button;
		Button to_menu_button;
		Button enter_button;
		Menu from_kind;
		Menu to_kind;

		Currency from;
		Currency to;

		double rate;

		static void cb_from_menu(Address, Address pw){ reference_to<Converter_window>(pw).from_menu(); }
		static void cb_to_menu(Address, Address pw){ reference_to<Converter_window>(pw).to_menu(); }
		static void cb_enter(Address, Address pw){ reference_to<Converter_window>(pw).enter(); }
		void from_menu(){ from_menu_button.hide(); to_kind.hide(); from_kind.show(); }
		void to_menu(){ to_menu_button.hide(); from_kind.hide(); to_kind.show(); }
		void enter();

		static void cb_from_jpy(Address, Address pw){ reference_to<Converter_window>(pw).from_jpy(); }
		static void cb_from_usd(Address, Address pw){ reference_to<Converter_window>(pw).from_usd(); }
		static void cb_to_jpy(Address, Address pw){ reference_to<Converter_window>(pw).to_jpy(); }
		static void cb_to_usd(Address, Address pw){ reference_to<Converter_window>(pw).to_usd(); }
		void from_jpy() { from_kind.hide(); from = JPY; inbox.label = "JPY"; from_menu_button.show(); }
		void from_usd() { from_kind.hide(); from = USD; inbox.label = "USD"; from_menu_button.show(); }
		void to_jpy() { to_kind.hide();  to = JPY; outbox.label = "JPY"; to_menu_button.show(); }
		void to_usd() { to_kind.hide(); to = USD; outbox.label = "USD"; to_menu_button.show(); }
	};

	void Converter_window::enter(){
		from_kind.hide();
		to_kind.hide();
		from_menu_button.show();
		to_menu_button.show();

		if(from == to) outbox.put(inbox.get_string());
		else if(from == JPY && to == USD) outbox.put(to_string(inbox.get_int() * (1 / rate)));
		else if(from == USD && to == JPY) outbox.put(to_string(inbox.get_int() * rate));
	}
}

int main(){
	using namespace Graph_lib;

	Converter_window win(Point(100, 100), 600, 400, "Converter");
	gui_main();
}