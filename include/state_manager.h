#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H
#define MAX_HISTORY_SIZE 5

struct State {
	void(*start)(void* data);
	void(*finish)(void* data);
	void(*update)(void* data, float dt);
	void(*draw)(void* data);
};

struct StateHistory {
	unsigned int start;
	unsigned int end;
	unsigned int count;
	unsigned int history[MAX_HISTORY_SIZE];
};

struct StateManager {
	struct State* states;
	unsigned int states_count;
	unsigned int active_state;
	struct StateHistory state_history;
};

void	stateManagerPopStateHistory(struct StateManager* state_manager);
void	pushStateHistory(struct StateManager* state_manager);
void	stateManagerInitialize(struct StateManager* state_manager, struct State* states, unsigned int states_count);
void	stateManagerSetState(struct StateManager* state_manager, unsigned int state, void* data);

#endif
