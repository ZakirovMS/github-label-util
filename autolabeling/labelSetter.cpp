#include "labelSetter.hpp"
#include <sstream>
#include "lib/httplib.h"
#include "lib/json.hpp"
#include "configCollector.hpp"

const std::string BASE_URL = "https://api.github.com";
const std::string ACCEPT_FORM = "application/vnd.github.v3+json";
const std::string USER_AGENT = "labelUtil";



LabelSetter::LabelSetter(std::string token, std::string owner, std::string repos):
  client_("https://api.github.com"),
  ownerGitHub_(owner),
  reposGitHub_(repos)
{
  client_.set_default_headers({{"Authorization", "token " + token}, {"Accept", ACCEPT_FORM}, {"User-Agent", USER_AGENT}});
}

nlohmann::json LabelSetter::getOpenPR()
{
  nlohmann::json allPrs = nlohmann::json::array();
  std::string urlGetOpenPR = "/repos/" + ownerGitHub_ + "/" + reposGitHub_ + "/pulls?state=open&per_page=100";
  
  while (!urlGetOpenPR.empty())
  {
    auto resultPRs = client_.Get(urlGetOpenPR.c_str());
    if (!resultPRs || resultPRs->status != 200)
    {
      throw std::runtime_error(resultPRs ? std::to_string(resultPRs->status) : "There is no answer");
    }

    auto pagePRs = nlohmann::json::parse(resultPRs->body);
    if (!pagePRs.is_array())
    {
      throw std::runtime_error("Invalid format");
    }

    allPrs.insert(allPrs.end(), pagePRs.begin(), pagePRs.end());

    if (resultPRs->has_header("Link"))
    {
        std::string linkHeader = resultPRs->get_header_value("Link");
        urlGetOpenPR = extractNextUrl(linkHeader);
    }
    else
    {
        urlGetOpenPR.clear();
    }
  }

  return allPrs;
}

void LabelSetter::setLabelsOnPRs(const nlohmann::json & listPR, const data::configCollector & generalData)
{
  for (const auto & onePR: listPR)
  {
    if (onePR["labels"].size() >= 2)
    {
      continue;
    }

    std::string githubName = onePR["user"]["login"];
    std::string title = onePR["title"];
    std::stringstream ss(title);

    std::pair< std::string, std::string > realName;
    std::getline(ss, realName.second, '.');
    std::getline(ss, realName.first, '\/');

    std::string labID;
    std::getline(ss, labID);

    std::vector< std::string > newLabels;
    newLabels.push_back(generalData.getLabLabel(labID));
    newLabels.push_back(generalData.getStudentsGrLabel(realName, githubName));

    setLabelsOnPR(onePR["number"], newLabels);
  }
}

void LabelSetter::setLabelsOnPR(int numPR, const std::vector< std::string > & labels)
{
  std::string urlSetLabelsOnPR = "/repos/" + ownerGitHub_ + "/" + reposGitHub_ + "/issues/" + std::to_string(numPR) + "/labels";
  nlohmann::json labelRequest = {{"labels", labels}};
  std::string body = labelRequest.dump();
  auto res_label = client_.Post(urlSetLabelsOnPR.c_str(), body, "application/json");

  if (!res_label || !(res_label->status == 200 || res_label->status == 201))
  {
    throw std::runtime_error(res_label ? std::to_string(res_label->status): "There is no answer");
  }
}

std::string LabelSetter::extractNextUrl(const std::string & linkHeader)
{
    if (linkHeader.empty())
    {
      return "";
    }

    size_t relPos = linkHeader.find("rel=\"next\"");
    if (relPos == std::string::npos)
    {
      return "";
    }

    size_t start = linkHeader.rfind('<', relPos);
    if (start == std::string::npos)
    {
      return "";
    }

    size_t end = linkHeader.find('>', start);
    if (end == std::string::npos)
    {
      return "";
    }

    return linkHeader.substr(start + 1, end - start - 1);
}
