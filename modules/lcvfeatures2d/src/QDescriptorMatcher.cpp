#include "QDescriptorMatcher.hpp"
#include "opencv2/features2d/features2d.hpp"

QDescriptorMatcher::QDescriptorMatcher(QQuickItem *parent)
    : QQuickItem(parent)
    , m_matcher(0)
    , m_matches(new QDMatchVector)
{
}

QDescriptorMatcher::QDescriptorMatcher(cv::DescriptorMatcher* matcher, QQuickItem *parent)
    : QQuickItem(parent)
    , m_matcher(matcher)
    , m_matches(new QDMatchVector)
{
}

QDescriptorMatcher::~QDescriptorMatcher(){
    delete m_matcher;
}

QDMatchVector* QDescriptorMatcher::matches(){
    return m_matches;
}

void QDescriptorMatcher::add(QMat* descriptors){
    if ( m_matcher ){
        std::vector<cv::Mat> descriptorVector;
        descriptorVector.push_back(*descriptors->cvMat());
        m_matcher->add(descriptorVector);
    }
}

void QDescriptorMatcher::train(){
    if ( m_matcher ){
        m_matcher->train();
        match(m_queryDescriptors, m_matches);
    }
}

void QDescriptorMatcher::match(QMat* queryDescriptors, QDMatchVector* matches){
    if ( m_matcher ){
        m_matcher->match(*queryDescriptors->cvMat(), matches->matches() );
    }
}

void QDescriptorMatcher::componentComplete(){
    QQuickItem::componentComplete();
    match(m_queryDescriptors, m_matches);
    emit matchesChanged();
}