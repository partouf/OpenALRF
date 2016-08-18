#pragma once

#include "../Common/CapturedImage.h"
#include <string>
#include <vector>

namespace OpenALRF
{
   class ImageProcessingSoftware
   {
   protected:
      CapturedImage Original;
      CapturedImage Grayscale;
      CapturedImage ObjectMask;

      void WriteToBMP(std::string AFilename, const OpenALRF::CapturedImage AImage);

      OpenALRF::CapturedImage ApplyMask3x3Median(double mask[3][3], const OpenALRF::CapturedImage AInputImage);
      OpenALRF::CapturedImage ApplyMask3x3(double mask[3][3], const OpenALRF::CapturedImage AInputImage);
      OpenALRF::CapturedImage ApplyMask5x5(double mask[5][5], const OpenALRF::CapturedImage AInputImage);
      OpenALRF::CapturedImage ApplyMask5x5SkipColor(double mask[5][5], const OpenALRF::CapturedImage AInputImage, unsigned char ASkipColor);
      OpenALRF::CapturedImage ApplyMask5x5Median(double mask[5][5], const OpenALRF::CapturedImage AInputImage);
      bool AllocateBuffer(CapturedImage *AImage);

      OpenALRF::CapturedImage DenoiseAndConnect(const OpenALRF::CapturedImage AInputImage);

      CapturedImage NewImageFromTemplate(const CapturedImage ATemplateImage);

      std::vector<unsigned char> GetDiffs(std::vector<unsigned char> ANumbers);
      unsigned char GetMedianForValue(std::vector<unsigned char> ANumbers);

      std::vector<unsigned char> BlowUpVectorContrast(std::vector<unsigned char> ANumbers);
      OpenALRF::CapturedImage PlaneDetection(const OpenALRF::CapturedImage AInputImage);
      
      OpenALRF::CapturedImage SimularityFill(const OpenALRF::CapturedImage AInputImage);

      OpenALRF::CapturedImage BlowUpImageContrast(const OpenALRF::CapturedImage AInputImage);
      OpenALRF::CapturedImage MakeMonoImage(const OpenALRF::CapturedImage AInputImage, unsigned char ACutoffPoint);
      OpenALRF::CapturedImage FindCutoffMakeMonoImage(const OpenALRF::CapturedImage AInputImage);

      bool MakeGrayscaleImage();
      unsigned char GetAverageGrayByte() const;
   public:
      ImageProcessingSoftware();
      ~ImageProcessingSoftware();

      void Initialize(const CapturedImage AImage);

      bool MakeObjectMask();
   };
};
