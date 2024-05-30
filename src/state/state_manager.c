#include <stdio.h>
#include <stdlib.h>
#include "../../include/state_manager.h"

void	pushStateHistory(struct StateManager* state_manager) {
	struct StateHistory* state_history = &state_manager->state_history;

	state_history->history[state_history->end] = state_manager->active_state;
	state_history->end = (state_history->end + 1) % MAX_HISTORY_SIZE;

	if (state_history->count == MAX_HISTORY_SIZE) {
		state_history->start = (state_history->start + 1) % MAX_HISTORY_SIZE;
	}

	state_history->count++;
}

void	stateManagerPopStateHistory(struct StateManager* state_manager) {
	struct StateHistory* state_history = &state_manager->state_history;

	if (state_history->count <= 0) {
		state_manager->active_state = 0;
		return;
	}

	if (state_history->end == 0) {
		state_history->end = MAX_HISTORY_SIZE - 1;
	} else {
		state_history->end = state_history->end - 1;
	}

	state_manager->active_state = state_history->history[state_history->end];
	state_history->end = state_history->end;
	state_history->count--;
}

struct State*	getActiveState(struct StateManager* state_manager) {
	return &(state_manager->states[state_manager->active_state]);
}

void	handleStart(struct StateManager* state_manager, void* data) {
	getActiveState(state_manager)->start(data);
}

void	handleFinish(struct StateManager* state_manager, void* data) {
	getActiveState(state_manager)->finish(data);
}

void	stateManagerUpdate(struct StateManager* state_manager, float dt, void* data) {
	getActiveState(state_manager)->update(data, dt);
}

void	stateManagerDraw(struct StateManager* state_manager, void* data) {
	getActiveState(state_manager)->draw(data);
}

void	stateManagerSetState(struct StateManager* state_manager, unsigned int state, void* data) {
	if (state >= state_manager->states_count) {
		return;
	}
	getActiveState(state_manager)->finish(data);
	pushStateHistory(state_manager);
	state_manager->active_state = state;
	getActiveState(state_manager)->start(data);
}

void	stateManagerInitialize(struct StateManager* state_manager, struct State* states, unsigned int states_count) {
	if (states_count <= 0) {
		perror("State initialized without states.");
		exit(1);
	}
	*state_manager = (struct StateManager){0};
	state_manager->states = states;
	state_manager->states_count = states_count;
	state_manager->state_history = (struct StateHistory){0};
}
