#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------
//  Name:   State.h
//  Desc:   abstract base class to define an interface for a state
//  Author: Programming Game AI by Example by Mat Buckland
//------------------------------------------------------------------------

template <class EntityType>
class State
{
public:

  virtual ~State(){}

  //this will execute when the state is entered;
  virtual void Enter(EntityType*) =0;
  
  //this is the states normal update function;
  virtual void Execute(EntityType*) =0;

  //this will execute when the state is exited;
  virtual void Exit(EntityType*) =0;

  virtual char* GetName() { return _name; }

  char* _name;
};

#endif