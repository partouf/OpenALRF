#include "SensorDictionary.h"

std::string OpenALRF::SensorDictionary::GetSensorName(OpenALRF::sensor_t ASensorID)
{
   if (ASensorID == OpenALRF::sensorUltrasonic) return "ultrasonic";
   else if (ASensorID == OpenALRF::sensorWheelEncoder) return "wheelencoder";
   else if (ASensorID == OpenALRF::sensorHumidity) return "humidity";
   else if (ASensorID == OpenALRF::sensorTemperature) return "temperature";
   else if (ASensorID == OpenALRF::sensorPressure) return "pressure";
   else if (ASensorID == OpenALRF::sensorGyroscope) return "gyroscope";
   else if (ASensorID == OpenALRF::sensorAccelerometer) return "accelerometer";
   else if (ASensorID == OpenALRF::sensorMagnetometer) return "magnetometer";

   return "unknown";
}

std::string OpenALRF::SensorDictionary::GetUnitSymbol(OpenALRF::sensorunit_t ASensorUnit)
{
   if (ASensorUnit == OpenALRF::unitPercentage) return "%";
   else if (ASensorUnit == OpenALRF::unitDegrees) return "" + 0xC2 + 0xB0;
   else if (ASensorUnit == OpenALRF::unitMeters) return "m";
   else if (ASensorUnit == OpenALRF::unitMetersPerSecond) return "m/s";
   else if (ASensorUnit == OpenALRF::unitG) return "g";
   else if (ASensorUnit == OpenALRF::unitMicroTesla) return 0xC2 + 0xB5 + "T";
   else if (ASensorUnit == OpenALRF::unitPascal) return "p";
   else if (ASensorUnit == OpenALRF::unitTicks) return "ticks";

   return "";
}

OpenALRF::sensor_t OpenALRF::SensorDictionary::GetSensorTypeFromName(const std::string AType)
{
   if (AType == "ultrasonic") return OpenALRF::sensorUltrasonic;
   else if (AType == "wheelencode") return OpenALRF::sensorWheelEncoder;
   else if (AType == "humidity") return OpenALRF::sensorHumidity;
   else if (AType == "temperature") return OpenALRF::sensorTemperature;
   else if (AType == "pressure") return OpenALRF::sensorPressure;
   else if (AType == "gyroscope") return OpenALRF::sensorGyroscope;
   else if (AType == "accelerometer") return OpenALRF::sensorAccelerometer;
   else if (AType == "magnetometer") return OpenALRF::sensorMagnetometer;

   return OpenALRF::sensorUnknown;
}

