#include "pintos_thread.h"

struct station {
	struct lock lock;
	struct condition cond_train_arrive; 
	struct condition cond_passenger_seated;
	int total_passengers;
	int total_seats;
	int total_in_wait;
	int total_on_board;
};

void
station_init(struct station *station)
{
	station->total_passengers = 0;
	station->total_seats = 0;
	station->total_in_wait = 0;
	lock_init(&station->lock);
	cond_init(&station->cond_train_arrive);
	cond_init(&station->cond_passenger_seated);
}

void
station_load_train(struct station *station, int count)
{
	lock_acquire(&station->lock);
	station->total_seats = count;
	while (station->total_on_board < station->total_seats && station->total_passengers) {
		cond_broadcast(&station->cond_train_arrive, &station->lock);
		cond_wait(&station->cond_passenger_seated, &station->lock);
	}
	station->total_in_wait = 0;
	station->total_seats = 0;
	station->total_on_board = 0;
	lock_release(&station->lock);
}

void
station_wait_for_train(struct station *station)
{
	lock_acquire(&station->lock);
	station->total_passengers++;
	while (station->total_seats <= station->total_in_wait)
		cond_wait(&station->cond_train_arrive, &station->lock);
	station->total_in_wait++;
	lock_release(&station->lock);
}

void
station_on_board(struct station *station)
{
	lock_acquire(&station->lock);
	station->total_passengers--;
	station->total_on_board++;
	cond_signal(&station->cond_passenger_seated, &station->lock);
	lock_release(&station->lock);
}
