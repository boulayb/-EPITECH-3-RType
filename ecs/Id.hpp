#ifndef ID_HPP_
# define ID_HPP_

# include <string>

class                           Id
{
  std::string                   _id;

 public:
  Id(const std::string& id) :
    _id(id)
  {
  }

  ~Id()
  {
  }

  inline void                   setId(const std::string& id)
  {
    _id = id;
  }

  inline const std::string&     getId(void) const
  {
    return (_id);
  }
};

inline bool                     operator==(const Id& left, const Id& right)
{
  return (left.getId() == right.getId());
}

#endif /* !ID_HPP_ */
