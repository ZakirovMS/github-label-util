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
    const std::string & getRule() const;
  private:
    std::string rule_;
    //todo
  };

  class configCollector
  {
  public:
    configCollector(std::ifstream & ifs);
    const std::vector< Student > & getStudents() const;
    const std::string & getStudentsGrLabel(std::pair< std::string, std::string > realName, std::string githubName) const;
    const std::vector< Dict > & getLabLabels() const;
    const std::string & getLabLabel(std::string lab) const;
    size_t getLabCount() const;
    const std::string & getTokenGitHub() const;
    const std::string & getOwnerGitHub() const;
    const std::string & getReposGitHub() const;
    const std::string & getBadPRLabel() const;
    const std::string & getBadBranchLabel() const;
    const std::string & getBadIssueLabel() const;
    const std::string & getFineLabel() const;
    const namingRule & getNamingPRRule() const;
    const namingRule & getNamingBranchRule() const;
  private:
    std::vector< Student > students_;
    std::vector< Dict > labLabels_;

    size_t labCount_;

    std::string tokenGitHub_;
    std::string ownerGitHub_;
    std::string reposGitHub_;

    std::string badPRLabel_;
    std::string badBranchLabel_;
    std::string badIssueLabel_;
    std::string fineLabel_;

    namingRule namingPR_;
    namingRule namingBranch_;

    void readStudent(std::ifstream & ifs);
    void readSpecialLabel(std::ifstream & ifs);
    void readLabLabel(std::ifstream & ifs);
    void readNamingRule(std::ifstream & ifs, data::namingRule & nr, char del = ',');
  };
}

#endif
