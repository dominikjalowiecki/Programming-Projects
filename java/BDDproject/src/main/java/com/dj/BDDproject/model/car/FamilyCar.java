package com.dj.BDDproject.model.car;

public class FamilyCar extends Car {

	public FamilyCar(int doorsCount, float engineSize, String brand) {
		super(doorsCount, engineSize, brand, CarType.FAMILY);
	}

}
