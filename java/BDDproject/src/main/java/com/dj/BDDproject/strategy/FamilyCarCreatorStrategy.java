package com.dj.BDDproject.strategy;

import com.dj.BDDproject.model.car.Car;
import com.dj.BDDproject.model.car.CarType;
import com.dj.BDDproject.model.car.FamilyCar;

public class FamilyCarCreatorStrategy implements CarCreatorStrategy {
	public Car createCar() {
		return new FamilyCar(4, 1.6F, "Skoda");
	}
	
	public CarType getCarType() {
		return CarType.FAMILY;
	}
}
