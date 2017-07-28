#include <boost/statechart/event.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <iostream>

namespace sc = boost::statechart;

struct Event1 : sc::event<Event1>
{
};

struct Event2 : sc::event<Event2>
{
};

struct SimpleState1;

struct StateMachine1 : sc::state_machine<StateMachine1, SimpleState1>
{
    StateMachine1(void)
    {
        std::cout << "construct StateMachine1" << std::endl;
    }

    ~StateMachine1(void)
    {
        std::cout << "distruct StateMachine1" << std::endl;
    }
};

struct SimpleState1_1;

struct SimpleState1 : sc::simple_state<SimpleState1, StateMachine1, SimpleState1_1>
{
//typedef sc::transition<Event1, SimpleState1> reactions;
    typedef boost::mpl::list <
        boost::statechart::custom_reaction< Event1 > > reactions;

    boost::statechart::result react(const Event1& ev)
    {
        std::cout << "hello world11111111111" << std::endl;
        return transit< SimpleState1 >();
    }

    SimpleState1(void)
    {
        std::cout << "enter SimpleState1" << std::endl;
    }

    ~SimpleState1(void)
    {
        std::cout << "leave SimpleState1" << std::endl;
    }
};

struct SimpleState1_2;

struct SimpleState1_1 : sc::simple_state<SimpleState1_1, SimpleState1>
{
//    typedef sc::transition<Event2, SimpleState1_2> reactions;
    typedef boost::mpl::list <
        boost::statechart::transition<Event1, SimpleState1_2>,
        boost::statechart::custom_reaction< Event2 > > reactions;

    boost::statechart::result react(const Event2 &ev)
    {
        std::cout << "ssssss enter 1-1" << std::endl;
        return transit< SimpleState1_1 >();
    }

    boost::statechart::result react(const Event1 &ev)
    {
        std::cout << "ssssss1-1 enter 1-2" << std::endl;
        return transit< SimpleState1_2 >();
    }

    SimpleState1_1(void)
    {
        std::cout << "enter SimpleState1_1" << std::endl;
    }

    ~SimpleState1_1(void)
    {
        std::cout << "leave SimpleState1_1" << std::endl;
    }
};

struct SimpleState1_2 : sc::simple_state<SimpleState1_2, SimpleState1>
{
    typedef sc::transition<Event2, SimpleState1_1> reactions;

    boost::statechart::result react(const Event2 &ev)
    {
        std::cout << "hello world" << std::endl;
    }

    SimpleState1_2(void)
    {
        std::cout << "enter SimpleState1_2" << std::endl;
    }

    ~SimpleState1_2(void)
    {
        std::cout << "leave SimpleState1_2" << std::endl;
    }
};

int main(int argc, char ** argv)
{
    StateMachine1 myMachine;
    myMachine.initiate();
    std::cout << "----- before process Event2" << std::endl;
    myMachine.process_event(Event2());
    std::cout << "----- after process Event2" << std::endl;
    std::cout << "----- before process Event1" << std::endl;
    myMachine.process_event(Event1());
    std::cout << "----- after process Event1" << std::endl;
    return 0;
}
