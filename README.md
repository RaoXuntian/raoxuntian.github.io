# Xuntian Rao Blog

This repository uses `master` as the maintainable source branch for the site. The old Hexo source history is still preserved on the `hexo` branch, but new edits should happen on `master`.

## Structure

- `source/_posts/`: blog posts in Markdown. Post images live in a matching folder under `source/_posts/`.
- `source/photography/`: photography pages. Each photo set is a Markdown page under `source/photography/<slug>/index.md`.
- `source/resume/`: the resume page source.
- `themes/xuntian/`: the current custom Hexo theme.
- `docs/`: generated GitHub Pages output. Do not edit files here by hand.

## Commands

```bash
npm install
npm run server
npm run build
```

`npm run build` generates the publishable site into `docs/`. GitHub Pages is configured to publish from `master` and `/docs`.
The `postbuild` script creates `docs/.nojekyll` automatically after each build.
There is no Hexo deploy step; commit the source changes and generated `docs/` output together.

## Add A Blog Post

Create a Markdown file in `source/_posts/`:

```markdown
---
title: My New Post
date: 2026-06-08
tags:
  - note
---

Write the post here.
```

If the post has images, create `source/_posts/my-new-post/` and reference images from the post.

## Add A Page

Create `source/<page-name>/index.md`:

```markdown
---
title: Page Title
comments: false
---

Page content here.
```

## Add A Photography Set

Create `source/photography/<slug>/index.md`:

```markdown
---
title: Photo Set Title
date: 2026-06-08
type: photo
cover: /photography/<slug>/cover.jpg
summary: One short line describing the set.
frame: Frame 06
camera_note: Natural light
frames:
  - image: /photography/<slug>/frame-02.jpg
    caption: Frame 02
comments: false
---

Photo notes here.

![A frame](/photography/<slug>/frame-02.jpg)
```

Put the images in the same folder. The photography index at `/photography/` will pick up pages with `type: photo`.
