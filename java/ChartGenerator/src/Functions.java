public enum Functions
{
	LINEAR_FUNCTION(false, false)
	{
		@Override
		public String toString()
		{
			return "Linear Function (ax + b)";
		}

		@Override
		public double getValue(FunctionParameters parameters)
		{
			double x = parameters.getX();
			double a = parameters.getA();
			double b = parameters.getB();
			
			return (a * x + b);
		}
	},
	SQUARE_FUNCTION(false, false)
	{
		@Override
		public String toString()
		{
			return "Square Function (ax^2 + bx + c)";
		}

		@Override
		public double getValue(FunctionParameters parameters)
		{
			double x = parameters.getX();
			double a = parameters.getA();
			double b = parameters.getB();
			double c = parameters.getC();
			
			return a * Math.pow(x, 2) + x * b + c;
		}
	},
	POWER_FUNCTION(false, true)
	{
		@Override
		public String toString()
		{
			return "Power Function (x^a)";
		}

		@Override
		public double getValue(FunctionParameters parameters)
		{
			double x = parameters.getX();
			double a = parameters.getA();
			
			if(x == 0.0 && a < 0)
			{
				return Double.POSITIVE_INFINITY;
			} else
				return Math.pow(x, a);
		}
	},
	CIRCLE_FUNCTION(true, true)
	{
		@Override
		public String toString()
		{
			return "Circle Function (x^2 + y^2 = a^2)";
		}

		@Override
		public double getValue(FunctionParameters parameters)
		{
			double x = parameters.getX();
			double a = parameters.getA();
			if(Math.abs(x) > Math.abs(a) || a <= 0)
				return Double.POSITIVE_INFINITY;
			else
				return Math.sqrt((a - x) * (a + x));
		}
	};
	
	public abstract String toString();
	public abstract double getValue(FunctionParameters parameters);
	
	private boolean isAbsolute;
	private boolean isMovable;
	
	Functions(boolean isAbsolute, boolean isMovable)
	{
		this.isAbsolute = isAbsolute;
		this.isMovable = isMovable;
	}
	
	
	public boolean getIfIsAbsolute()
	{
		return this.isAbsolute;
	}
	
	public boolean getIfIsMovable()
	{
		return this.isMovable;
	}
}