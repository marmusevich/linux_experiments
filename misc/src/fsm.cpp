#include <boost/msm/front/euml/euml.hpp>
#include <boost/msm/front/euml/state_grammar.hpp>
#include <boost/msm/back/state_machine.hpp>

#include <boost/msm/back/tools.hpp>
#include <boost/msm/back/metafunctions.hpp>
#include <boost/mpl/for_each.hpp>


#include <iostream>





//------------------------------------------------------------------
//Examples from https://theboostcpplibraries.com/boost.msm
namespace NExample_1
{
	namespace msm = boost::msm;
	using namespace boost::msm::front::euml;

	BOOST_MSM_EUML_STATE((), Off)
	BOOST_MSM_EUML_STATE((), On)

	BOOST_MSM_EUML_EVENT(press)

	BOOST_MSM_EUML_TRANSITION_TABLE((
		Off + press == On,
		On + press == Off
		), light_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
		(light_transition_table, init_ << Off),
		light_state_machine)

	void main()
	{
		msm::back::state_machine<light_state_machine> light;
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
	}

}

namespace NExample_2
{
	namespace msm = boost::msm;
	using namespace boost::msm::front::euml;

	BOOST_MSM_EUML_STATE((), Off)
	BOOST_MSM_EUML_STATE((), On)

	BOOST_MSM_EUML_EVENT(press)

	BOOST_MSM_EUML_ACTION(switch_light)
	{
		template <class Event, class Fsm>
		void operator()(const Event & ev, Fsm & fsm,
			BOOST_MSM_EUML_STATE_NAME(Off) & sourceState,
			BOOST_MSM_EUML_STATE_NAME(On) & targetState) const
		{
			std::cout << "Switching on\n";
			std::cout << *fsm.current_state() << '\n'; // NOTE: curent state is off, i.e. it is 'before' sweetch callback

		}

		template <class Event, class Fsm>
		void operator()(const Event & ev, Fsm & fsm,
			decltype(On) & sourceState,
			decltype(Off) & targetState) const
		{
			std::cout << "Switching off\n";
		}
	};

	BOOST_MSM_EUML_TRANSITION_TABLE((
		Off + press / switch_light == On,
		On + press / switch_light == Off
		), light_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
		(light_transition_table, init_ << Off),
		light_state_machine)

	void main()
	{
		msm::back::state_machine<light_state_machine> light;
		std::cout << *light.current_state() << '\n';

		light.process_event(press);
		std::cout << *light.current_state() << '\n';

		light.process_event(press);
		std::cout << *light.current_state() << '\n';

	}
}

namespace NExample_3
{
	namespace msm = boost::msm;
	using namespace boost::msm::front::euml;

	BOOST_MSM_EUML_STATE((), Off)
	BOOST_MSM_EUML_STATE((), On)

	BOOST_MSM_EUML_EVENT(press)

	BOOST_MSM_EUML_ACTION(is_broken)
	{
		template <class Event, class Fsm, class Source, class Target>
		bool operator()(const Event & ev, Fsm & fsm, Source & src, Target & trg) const
		{
			return true;
		}
	};

	BOOST_MSM_EUML_ACTION(switch_light)
	{
		template <class Event, class Fsm, class Source, class Target>
		void operator()(const Event & ev, Fsm & fsm, Source & src, Target & trg) const
		{
			std::cout << "Switching\n";
		}
	};

	BOOST_MSM_EUML_TRANSITION_TABLE((
		Off + press[!is_broken] / switch_light == On,
		On + press / switch_light == Off
		), light_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
		(light_transition_table, init_ << Off),
		light_state_machine)

	void main()
	{
		msm::back::state_machine<light_state_machine> light;
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
	}
}

namespace NExample_4
{
	namespace msm = boost::msm;
	using namespace boost::msm::front::euml;

	BOOST_MSM_EUML_ACTION(state_entry)
	{
		template <class Event, class Fsm, class State>
		void operator()(const Event & ev, Fsm & fsm, State & state) const
		{
			std::cout << "Entering  " << *fsm.current_state() << '\n';
		}
	};

	BOOST_MSM_EUML_ACTION(state_exit)
	{
		template <class Event, class Fsm, class State>
		void operator()(const Event & ev, Fsm & fsm, State & state) const
		{
			std::cout << "Exiting  " << *fsm.current_state() << '\n';
		}
	};

	BOOST_MSM_EUML_STATE((state_entry, state_exit), Off)
	BOOST_MSM_EUML_STATE((state_entry, state_exit), On)

	BOOST_MSM_EUML_EVENT(press)

	BOOST_MSM_EUML_TRANSITION_TABLE((
		Off + press == On,
		On + press == Off
		), light_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
		(light_transition_table, init_ << Off),
		light_state_machine)

	void main()
	{
		msm::back::state_machine<light_state_machine> light;
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';

	}
}

namespace NExample_5
{
	namespace msm = boost::msm;
	using namespace boost::msm::front::euml;

	BOOST_MSM_EUML_DECLARE_ATTRIBUTE(int, switched_on)

	BOOST_MSM_EUML_ACTION(state_entry)
	{
		template <class Event, class Fsm, class State>
		void operator()(const Event & ev, Fsm & fsm, State & state) const
		{
			std::cout << "Switched on\n";
			++fsm.get_attribute(switched_on);
		}
	};
	BOOST_MSM_EUML_ACTION(is_broken)
	{
		template <class Event, class Fsm, class Source, class Target>
		bool operator()(const Event & ev, Fsm & fsm, Source & src, Target & trg) const
		{
			return fsm.get_attribute(switched_on) > 1;
		}
	};

	BOOST_MSM_EUML_STATE((), Off)
	BOOST_MSM_EUML_STATE((state_entry), On)
	BOOST_MSM_EUML_EVENT(press)

	BOOST_MSM_EUML_TRANSITION_TABLE((
		Off + press[!is_broken] == On,
		On + press == Off
		), light_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
		(light_transition_table, init_ << Off, no_action, no_action,
			attributes_ << switched_on), light_state_machine)

	void main()
	{
		msm::back::state_machine<light_state_machine> light;
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
	}
}

namespace NExample_6
{
	namespace msm = boost::msm;
	using namespace boost::msm::front::euml;

	BOOST_MSM_EUML_DECLARE_ATTRIBUTE(int, switched_on)

	void write_message()
	{
		std::cout << "Switched on\n";
	}

	BOOST_MSM_EUML_FUNCTION(WriteMessage_, write_message, write_message_,
		void, void)

	BOOST_MSM_EUML_STATE((), Off)
	BOOST_MSM_EUML_STATE((), On)

	BOOST_MSM_EUML_EVENT(press)

	BOOST_MSM_EUML_TRANSITION_TABLE((
		Off + press[fsm_(switched_on) < Int_<2>()] / (++fsm_(switched_on),	write_message_()) == On,
		On + press == Off
		), light_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
		(light_transition_table, init_ << Off, no_action, no_action,
			attributes_ << switched_on), light_state_machine)

	void main()
	{
		msm::back::state_machine<light_state_machine> light;
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
		light.process_event(press);
		std::cout << *light.current_state() << '\n';
	}
}


//------------------------------------------------------------------
namespace NExercises
{
	/*
		1. Create a state machine for a window that can be closed, opened or tilted. 
		   A closed window can be opened or tilted. An open window can’t be tilted though without closing it first. 
		   Nor can a tilted window be opened without closing it first. 
		   Test your state machine by opening and tilting your window a couple of times. 
		   Use current_state() to write states to standard output.
	*/

	namespace msm = boost::msm;
	using namespace boost::msm::front::euml;

	//windows state - ws
	BOOST_MSM_EUML_STATE((), ws_closed)
	BOOST_MSM_EUML_STATE((), ws_opened)
	BOOST_MSM_EUML_STATE((), ws_tilted)

	//windows action - wa
	BOOST_MSM_EUML_EVENT(wa_close)
	BOOST_MSM_EUML_EVENT(wa_open)
	BOOST_MSM_EUML_EVENT(wa_tilt)

	BOOST_MSM_EUML_TRANSITION_TABLE((
		ws_closed + wa_open == ws_opened,
		ws_opened + wa_close == ws_closed,
		ws_closed + wa_tilt == ws_tilted,
		ws_tilted + wa_close == ws_closed
		), window_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
		(window_transition_table, init_ << ws_closed),
		window_state_machine)


	std::string getStateName(int stateId) 
	{
		switch (stateId)
		{
		case 0: return "closed";
		case 1: return "opened";
		case 2: return "tilted";

		}
		return "__UNCNOWN__";
	}

	template<class FSM>
	std::string getCurStateName(const FSM& fsm)
	{
		return getStateName(*fsm.current_state());
	}

#define DO_CASE(action) \
do \
{ \
	fsmWindow.process_event(action); \
	std::cout << "The action is <"#action">, state change to --> " << getCurStateName(fsmWindow) << "\n"; \
} \
while (false)
//[END] DO_CASE


	void main()
	{
		msm::back::state_machine<window_state_machine> fsmWindow;

		std::cout << "START STATE: " << getCurStateName(fsmWindow) << '\n';
		std::cout << "--- NORMAL ---\n";

		DO_CASE(wa_close);
		DO_CASE(wa_open);
		DO_CASE(wa_close);
		DO_CASE(wa_tilt);
		DO_CASE(wa_close);


		std::cout << "--- TRY tilt opened  ---\n";
		DO_CASE(wa_close);
		DO_CASE(wa_open);
		DO_CASE(wa_tilt);
		DO_CASE(wa_close);

		std::cout << "--- TRY open tilted  ---\n";
		DO_CASE(wa_close);
		DO_CASE(wa_tilt);
		DO_CASE(wa_open);
		DO_CASE(wa_close);
	}


#undef DO_CASE
}



void fsm_main()
{
	std::cout << "\n---------------------------------------------------------------\n" << "#1\n";
	NExample_1::main();
	std::cout << "\n---------------------------------------------------------------\n" << "#2\n";
	NExample_2::main();
	std::cout << "\n---------------------------------------------------------------\n" << "#3\n";
	NExample_3::main();
	std::cout << "\n---------------------------------------------------------------\n" << "#4\n";
	NExample_4::main();
	std::cout << "\n---------------------------------------------------------------\n" << "#5\n";
	NExample_5::main();
	std::cout << "\n---------------------------------------------------------------\n" << "#6\n";
	NExample_6::main();

	std::cout << "\n---------------------------------------------------------------\n" << "#6\n";
	NExercises::main();

}

