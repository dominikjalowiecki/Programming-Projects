package com.dj.BDDproject.strategy;

import com.dj.BDDproject.model.car.Car;
import com.dj.BDDproject.model.car.CarType;
import com.dj.BDDproject.model.car.TruckCar;

public class TruckCarCreatorStrategy implements CarCreatorStrategy {
	public Car createCar() {
		return new TruckCar(2, 5.0F, "Scania");
	}
	
	public CarType getCarType() {
		return CarType.TRUCK;
	}
}
