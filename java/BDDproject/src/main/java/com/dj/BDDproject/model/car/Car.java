package com.dj.BDDproject.model.car;

public abstract class Car {
	private int doorsCount;
	private float engineSize;
	private String brand;
	private CarType carType;
	
	public Car(int doorsCount, float engineSize, String brand, CarType carType) {
		this.setDoorsCount(doorsCount);
		this.setEngineSize(engineSize);
		this.setBrand(brand);
		this.setCarType(carType);
	}

	public int getDoorsCount() {
		return doorsCount;
	}

	public void setDoorsCount(int doorsCount) {
		this.doorsCount = doorsCount;
	}

	public float getEngineSize() {
		return engineSize;
	}

	public void setEngineSize(float engineSize) {
		this.engineSize = engineSize;
	}

	public String getBrand() {
		return brand;
	}

	public void setBrand(String brand) {
		this.brand = brand;
	}
	
	@Override
	public String toString() {
		return String.format("%s :: %.1fL :: %d :: %s", brand, engineSize, doorsCount, carType);
	}

	public CarType getCarType() {
		return carType;
	}

	public void setCarType(CarType carType) {
		this.carType = carType;
	}
}
