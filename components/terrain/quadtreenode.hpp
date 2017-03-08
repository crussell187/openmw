#ifndef OPENMW_COMPONENTS_TERRAIN_QUADTREENODE_H
#define OPENMW_COMPONENTS_TERRAIN_QUADTREENODE_H

#include <osg/Group>

#include "defs.hpp"

namespace Terrain
{

    enum ChildDirection
    {
        NW = 0,
        NE = 1,
        SW = 2,
        SE = 3,
        Root
    };

    class QuadTreeNode;
    class LodCallback : public osg::Referenced
    {
    public:
        virtual ~LodCallback() {}

        virtual bool isSufficientDetail(QuadTreeNode *node, osg::NodeVisitor &nv) = 0;
    };

    class ViewDataMap;
    class ViewData;

    class QuadTreeNode : public osg::Group
    {
    public:
        QuadTreeNode(QuadTreeNode* parent, ChildDirection dir, float size, const osg::Vec2f& center);
        virtual ~QuadTreeNode();

        QuadTreeNode* getParent();

        QuadTreeNode* getChild(unsigned int i);
        using osg::Group::getNumChildren;

        /// Returns our direction relative to the parent node, or Root if we are the root node.
        ChildDirection getDirection() { return mDirection; }

        /// Get neighbour node in this direction
        QuadTreeNode* getNeighbour (Direction dir);

        /// Initialize neighbours - do this after the quadtree is built
        void initNeighbours();

        void setBoundingBox(const osg::BoundingBox& boundingBox);
        const osg::BoundingBox& getBoundingBox() const;

        virtual osg::BoundingSphere computeBound() const;

        /// size in cell coordinates
        float getSize() const;

        /// center in cell coordinates
        const osg::Vec2f& getCenter() const;

        virtual void traverse(osg::NodeVisitor& nv);

        /// Set the Lod callback to use for determining when to stop traversing further down the quad tree.
        void setLodCallback(LodCallback* lodCallback);

        /// Set the view data map that the finally used nodes for a given camera/intersection are pushed onto.
        void setViewDataMap(ViewDataMap* map);

        ViewDataMap* getViewDataMap();

        /// Create or retrieve a view for the given traversal.
        ViewData* getView(osg::NodeVisitor& nv);

    private:
        QuadTreeNode* mParent;

        QuadTreeNode* mNeighbours[4];

        ChildDirection mDirection;

        osg::BoundingBox mBoundingBox;
        float mSize;
        osg::Vec2f mCenter;

        osg::ref_ptr<LodCallback> mLodCallback;

        osg::ref_ptr<ViewDataMap> mViewDataMap;
    };

}

#endif