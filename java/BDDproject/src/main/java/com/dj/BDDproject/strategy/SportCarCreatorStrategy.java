package com.dj.BDDproject.strategy;

import com.dj.BDDproject.model.car.Car;
import com.dj.BDDproject.model.car.CarType;
import com.dj.BDDproject.model.car.SportCar;

public class SportCarCreatorStrategy implements CarCreatorStrategy  {
	public Car createCar() {
		return new SportCar(2, 3.0F, "Ferrari");
	}
	
	public CarType getCarType() {
		return CarType.SPORT;
	}
}
