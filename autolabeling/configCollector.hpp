#ifndef PARCECONFIG_HPP
#define PARCECONFIG_HPP

#include <vector>
#include <string>
#include <fstream>
namespace data
{
  using Dict = std::pair< std::string, std::string >;

  struct Student
  {
    std::pair< std::string, std::string > fullRealName;
    std::string githubName;
    std::string groupLabel;
  };

  class namingRules
  {
  public:
    namingRules(std::string & rule);
    void showRule();
  private:
    std::string rule_;
    //todo
  };

  class configCollector
  {
  public:

  private:
    std::vector< Student > students_;
    std::vector< Dict > labLabels_;
    std::vector< Dict > groupLabels_;

    std::string badPRLabel_;
    std::string badBranchLabel_;
    std::string badIssueLabel_;
    std::string fineLabel_;

    namingRules namingPR_;
    namingRules namingBranch_;

    void readStudents(std::ifstream & ifs);
    void readLabels(std::ifstream & ifs);
    void readNamingRules(std::ifstream & ifs);
  };
}

#endif
