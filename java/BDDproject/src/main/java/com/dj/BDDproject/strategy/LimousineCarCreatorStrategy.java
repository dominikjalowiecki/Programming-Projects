package com.dj.BDDproject.strategy;

import com.dj.BDDproject.model.car.Car;
import com.dj.BDDproject.model.car.CarType;
import com.dj.BDDproject.model.car.LimousineCar;

public class LimousineCarCreatorStrategy implements CarCreatorStrategy {
	public Car createCar() {
		return new LimousineCar(6, 2.0F, "Mercedes");
	}
	
	public CarType getCarType() {
		return CarType.LIMOUSINE;
	}
}
