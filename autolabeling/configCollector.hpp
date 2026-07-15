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

  class namingRule
  {
  public:
    void setRule(const std::string & rule);
    const std::string & getRule();
  private:
    std::string rule_;
    //todo
  };

  class configCollector
  {
  public:
    configCollector(std::ifstream & ifs);
  private:
    std::vector< Student > students_;
    std::vector< Dict > labLabels_;
    std::vector< Dict > groupLabels_;

    std::string badPRLabel_;
    std::string badBranchLabel_;
    std::string badIssueLabel_;
    std::string fineLabel_;

    namingRule namingPR_;
    namingRule namingBranch_;

    void readStudent(std::ifstream & ifs);
    void readSpecialLabel(std::ifstream & ifs);
    void readLabLabel(std::ifstream & ifs);
    void readNamingRule(std::ifstream & ifs);
  };
}

#endif
