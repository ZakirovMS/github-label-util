#ifndef LABELSETTER_HPP
#define LABELSETTER_HPP
#include <string>
#include <list>
#include "lib/httplib.h"
#include "lib/json.hpp"
#include "configCollector.hpp"

class LabelSetter
{
public:
  LabelSetter(std::string token, std::string owner, std::string repos);
  nlohmann::json getOpenPR();
  void setLabelsOnPRs(const nlohmann::json & listPR, const data::configCollector & studentsData);
  void setLabelsOnPR(int numPR, const std::vector< std::string > & labels);
private:
  httplib::Client client_;
  std::string ownerGitHub_;
  std::string reposGitHub_;
  std::string extractNextUrl(const std::string & linkHeader);
};

#endif
